#pragma once

#include "pch.h"
#include "Socket.h"
#include "Session.h"
#include "Overlapped.h"

class CAcceptor : public COverlapped
{
public:
	CAcceptor() : COverlapped(COverlapped::eFLAG::eAccept) {}

	void Set(shared_ptr<CSession> session, SOCKET listenSock) 
	{ 
		_mSession = session;
		_mListenSock = listenSock;
	}

	virtual void PacketProcess() override
	{
		if (!CSocket::SetSocketOpt(_mSession->GetSocket(), SO_UPDATE_ACCEPT_CONTEXT, _mListenSock))
		{
			runtime_error("SetSocketOpt");
		}
	}

private:
	shared_ptr<CSession>	_mSession;
	SOCKET					_mListenSock = INVALID_SOCKET;
};