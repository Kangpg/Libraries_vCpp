#pragma once

#include "pch.h"
#include "Overlapped.h"

class CSession;
class CAcceptor : public COverlapped
{
public:
	CAcceptor() : COverlapped(COverlapped::eFLAG::eAccept) {}

	bool Listen(const SOCKADDR_IN& addr)
	{


		return true;
	}

	void SetSession(shared_ptr<CSession> session) { _mSession = session; }

	virtual void PacketProcess() override
	{

	}

private:
	shared_ptr<CSession>	_mSession;
};

class CConnector : public COverlapped
{
public:
	CConnector() : COverlapped(COverlapped::eFLAG::eConnect) {}

	virtual void PacketProcess() override {};
};

class CDisConnector : public COverlapped
{
public:
	CDisConnector() : COverlapped(COverlapped::eFLAG::eDisconnect) {}

	virtual void PacketProcess() override {};
};

class CSender : public COverlapped
{
public:
	CSender() : COverlapped(COverlapped::eFLAG::eSend) {}

	virtual void PacketProcess() override {};
};

class CReceiver : public COverlapped
{
public:
	CReceiver() : COverlapped(COverlapped::eFLAG::eReceive) {}

	virtual void PacketProcess() override {};
};