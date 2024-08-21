#pragma once

#include "pch.h"
#include "Socket.h"
#include "Session.h"
#include "Overlapped.h"

class CAcceptor : public COverlapped
{
public:
	CAcceptor();

	void Set(shared_ptr<CSession> session, SOCKET listenSock);

	virtual void PacketProcess() override;

private:
	shared_ptr<CSession>	_mSession;
	SOCKET					_mListenSock = INVALID_SOCKET;
};