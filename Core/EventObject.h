#pragma once

#include "Overlapped.h"

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