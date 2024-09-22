#pragma once

#include "pch.h"
#include "../Core/Protocol.h"
#include "Protocol.pb.h"

#define REGIST_HANDLER(packetid)				case ePacketId::packetid: CPacketHandler::Handler_##packetid(session, buffer, size); break
#define DEFINE_HANDLER(packetid)				static void Handler_##packetid(shared_ptr<CSession>& session, BYTE* buffer, uint32 size)
#define IMPL_HANDLER(packetid)					void CPacketHandler::Handler_##packetid(shared_ptr<CSession> session, BYTE* buffer, uint32 size)

class CSession;
class CPacketHandler
{
public:
	CPacketHandler() = default;

	static bool HandlePacket(shared_ptr<CSession> session, int32 id, BYTE* buffer, uint32 size)
	{
		switch (static_cast<ePacketId>(id))
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
		if (!packet.ParseFromArray(buffer, size))
		{
			// ERR
			return;
		}

		// TODO
	}
};