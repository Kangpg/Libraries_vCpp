#pragma once

#include "../Core/Session.h"
#include "PacketHandler.h"

class CServerSession : public CSession
{
public:
	CServerSession() = default;
	virtual ~CServerSession() = default;

protected:
	virtual void OnConnected() {}
	virtual void OnDisConnected() {}
	virtual void OnReceived(BYTE* buffer, uint32 len) 
	{
		sHeader* header = reinterpret_cast<sHeader*>(buffer);

		if (!CPacketHandler::HandlePacket(shared_from_this(), buffer, len))
		{
			::runtime_error("OnReceived");
		}
	}
	virtual void OnSend() {}
};

