#include "pch.h"
#include "Session.h"

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

void CSession::OnReceived()
{

}

void CSession::OnConnected()
{

}

void CSession::OnDisconnected()
{

}