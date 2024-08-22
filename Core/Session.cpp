#include "pch.h"
#include "Session.h"

CSession::CSession()
	: _mConnector(shared_from_this()), _mDisConnector(shared_from_this()), _mSender(shared_from_this()), _mReceiver(shared_from_this())
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

SOCKET CSession::GetSocket() const 
{ 
	return _mSock;
}

void CSession::SendPacket(::WSABUF& buf)
{
	{
		lock_guard<std::mutex> lock(_mMutex);

		/*auto ret = ::WSASend(_mSock, &buf, buf.len, )*/
	}
}

void CSession::OnReceived(DWORD recvBytes)
{
	// disconnected
	if (recvBytes == 0)
	{
		OnDisconnected();
		return;
	}

	if (!_mRecvBuf.MoveHead(recvBytes))
	{
		OnDisconnected();
		return;
	}

	{
		// Pop data and process contents func

		if (!_mRecvBuf.MoveRear(recvBytes)) // readable
		{
			OnDisconnected();
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

void CSession::OnConnected()
{
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

void CSession::OnDisconnected()
{

}