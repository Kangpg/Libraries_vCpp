#include "pch.h"
#include "EventObject.h"
#include "Server.h"
#include "Session.h"

CAcceptor::CAcceptor()
	: COverlapped(COverlapped::eFLAG::eAccept)
{

}

CAcceptor::CAcceptor(shared_ptr<CServer> server, SOCKET listenSocket)
	: COverlapped(COverlapped::eFLAG::eAccept), _mServer(server), _mListenSock(listenSocket)
{

}

void CAcceptor::Init(shared_ptr<CSession> session)
{
	_mSession = session;
}

void CAcceptor::PacketProcess(DWORD recvBytes)
{
	if (!CSocket::SetSocketOpt(_mSession->GetSocket(), SO_UPDATE_ACCEPT_CONTEXT, _mListenSock))
		::runtime_error("SetSocketOpt");

	_mSession->OnSessionConnected();

	// TODO : 세션 등록 후 다시 Accept

	// TODO : 함수화
	if (!AcceptSocket())
		::runtime_error("AcceptSocket");
}

bool CAcceptor::RegistSocket(SOCKET socket)
{
	return _mServer->_mIocp.RegistHandle(reinterpret_cast<HANDLE>(socket));
}

bool CAcceptor::AcceptSocket()
{
	auto session = _mServer->_mSessionManager.CreateSession();
	if (!session)
		return false;

	Init(session);
	RegistSocket(session->GetSocket());

	DWORD bytes = 0; // async
	if (!CSocket::AcceptEx(_mListenSock, session->GetSocket(), session->_mRecvBuf.GetHeadPos(), 0, sizeof(SOCKADDR_IN) + 16, sizeof(SOCKADDR_IN) + 16, &bytes, static_cast<LPOVERLAPPED>(this)))
	{
		if (WSA_IO_PENDING == ::WSAGetLastError())
		{
			// 재시도?
			return true;
		}
		else
		{
			PrintWSAError("AcceptEx");
			return false;
		}
	}

	return true;
}

CConnector::CConnector()
	: COverlapped(COverlapped::eFLAG::eConnect)
{

}

void CConnector::Init(weak_ptr<CSession> session)
{
	_mSession = session;
}

void CConnector::PacketProcess(DWORD recvBytes)
{

}

CDisConnector::CDisConnector()
	: COverlapped(COverlapped::eFLAG::eDisconnect)
{

}

void CDisConnector::Init(weak_ptr<CSession> session)
{
	_mSession = session;
}

void CDisConnector::PacketProcess(DWORD recvBytes)
{

}

CSender::CSender()
	: COverlapped(COverlapped::eFLAG::eSend)
{

}

void CSender::Init(weak_ptr<CSession> session)
{
	_mSession = session;
}

void CSender::PacketProcess(DWORD recvBytes)
{

}

CReceiver::CReceiver()
	: COverlapped(COverlapped::eFLAG::eReceive)
{
	
}

void CReceiver::Init(weak_ptr<CSession> session)
{
	_mSession = session;
}

void CReceiver::PacketProcess(DWORD recvBytes)
{
	if(auto session = _mSession.lock())
		session->OnSessionReceived(recvBytes);
}