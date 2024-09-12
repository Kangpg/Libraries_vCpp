#pragma once

#include "../Core/Session.h"
#include "PacketHandler.h"

class CServerSession : public CSession
{
public:
	CServerSession() = default;
	virtual ~CServerSession() = default;

protected:
	virtual void OnConnected() override {}
	virtual void OnDisConnected() override {}
	virtual void OnReceived(BYTE* buffer, uint32 len) override;
	virtual void OnSend() override {}
};

