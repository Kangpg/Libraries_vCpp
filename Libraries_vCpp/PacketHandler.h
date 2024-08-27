#pragma once

#include "pch.h"
#include "../Core/Protocol.h"
#include "Protocol.pb.h"

#define REGIST_HANDLER(packetid)				case ePacketId::packetid: CPacketHandler::Handler_##packetid(session, buffer, size); break
#define DEFINE_HANDLER(packetid)				void Handler_##packetid(shared_ptr<CSession>& session, BYTE* buffer, uint32 size)
#define IMPL_HANDLER(packetid)					void CPacketHandler::Handler_##packetid(shared_ptr<CSession> session, BYTE* buffer, uint32 size)

class CSession;
class CPacketHandler
{
public:
	CPacketHandler() = default;

	bool HandlePacket(ePacketId packetid, shared_ptr<CSession>& session, BYTE* buffer, uint32 size)
	{
		switch (packetid)
		{
			REGIST_HANDLER(PACKET_SC_CHAT);

		default:
			// Packet Err
			return false;
		}

		return true;
	}

	// DEFINE HANDLER
	DEFINE_HANDLER(PACKET_SC_CHAT)
	{
		Protocol::PACKET_SC_CHAT packet;
		if (!packet.ParseFromArray(buffer + sizeof(sHeader), size - sizeof(sHeader)))
		{
			// ERR
			return;
		}

		
	}
};