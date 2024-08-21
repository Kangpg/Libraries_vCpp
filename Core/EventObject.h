#pragma once

#include "Overlapped.h"

class CConnector : public COverlapped
{
public:
	CConnector();

	virtual void PacketProcess() override;
};

class CDisConnector : public COverlapped
{
public:
	CDisConnector();

	virtual void PacketProcess() override;
};

class CSender : public COverlapped
{
public:
	CSender();

	virtual void PacketProcess() override;
};

class CReceiver : public COverlapped
{
public:
	CReceiver();

	virtual void PacketProcess() override;
};