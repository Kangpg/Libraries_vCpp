#include "pch.h"
#include "Session.h"
#include "Protocol.h"

CSession::CSession()
{
	_mSock = CSocket::CreateSocket(WSA_FLAG_OVERLAPPED);
	if (_mSock == INVALID_SOCKET)
	{
		runtime_error("CSocket::CreateSocket");
	}
}

CSession::~CSession()
{
	if (_mSock != INVALID_SOCKET)
	{
		closesocket(_mSock);
		_mSock = INVALID_SOCKET;
	}
}

void CSession::Init()
{
	_mConnector.Init(weak_from_this());
	_mDisConnector.Init(weak_from_this());
	_mSender.Init(weak_from_this());
	_mReceiver.Init(weak_from_this());
}

SOCKET CSession::GetSocket() const 
{ 
	return _mSock;
}

void CSession::SendPacket(::WSABUF& buf)
{
	if (_mSendBuf.IsEmpty())
		return;
	
	DWORD bytes = 0;
	if (SOCKET_ERROR == ::WSASend(_mSock, &buf, buf.len, &bytes, 0, &_mSender, nullptr))
	{
		if (::WSAGetLastError() != WSA_IO_PENDING)
		{
			::runtime_error("WSASend");
		}
	}

	_mSendBuf.MoveRear(buf.len);
}

void CSession::OnSessionReceived(DWORD recvBytes)
{
	// disconnected
	if (recvBytes == 0)
	{
		OnDisConnected();
		return;
	}

	if (!_mRecvBuf.MoveHead(recvBytes))
	{
		OnDisConnected();
		return;
	}

	{
		

		sHeader* header = reinterpret_cast<sHeader*>(_mRecvBuf.GetRearPos());
		if (header == nullptr)
		{
			::runtime_error("OnSessionReceived");
		}
		else
		{
			// Pop data and process contents func
			OnReceived(header->mPacketId, _mRecvBuf.GetRearPos() + sizeof(sHeader), header->mSize);
		}

		if (!_mRecvBuf.MoveRear(recvBytes)) // readable
		{
			OnDisConnected();
			return;
		}
	}

	// Func
	::WSABUF wsabuf;
	wsabuf.buf = reinterpret_cast<char*>(_mRecvBuf.GetHeadPos());
	wsabuf.len = static_cast<ULONG>(_mRecvBuf.GetUsable());

	DWORD bytes = 0;
	DWORD flags = 0;
	if (SOCKET_ERROR == ::WSARecv(_mSock, &wsabuf, 1, &bytes, &flags, &_mReceiver, nullptr))
	{
		::runtime_error("WSARecv error");
	}

	return;
}

void CSession::OnSessionConnected()
{
	OnConnected();

	::WSABUF wsabuf;
	wsabuf.buf = reinterpret_cast<char*>(_mRecvBuf.GetHeadPos());
	wsabuf.len = static_cast<ULONG>(_mRecvBuf.GetUsable());

	DWORD bytes = 0;
	DWORD flags = 0;
	if (SOCKET_ERROR == ::WSARecv(_mSock, &wsabuf, 1, &bytes, &flags, &_mReceiver, nullptr))
	{
		::runtime_error("WSARecv error");
	}
}