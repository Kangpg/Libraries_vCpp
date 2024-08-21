#include "pch.h"
#include "Acceptor.h"

CAcceptor::CAcceptor()
	: COverlapped(COverlapped::eFLAG::eAccept)
{

}

void CAcceptor::Set(shared_ptr<CSession> session, SOCKET listenSock)
{
	_mSession = session;
	_mListenSock = listenSock;
}

void CAcceptor::PacketProcess()
{
	if (!CSocket::SetSocketOpt(_mSession->GetSocket(), SO_UPDATE_ACCEPT_CONTEXT, _mListenSock))
	{
		runtime_error("SetSocketOpt");
	}
}