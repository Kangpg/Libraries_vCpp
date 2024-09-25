#pragma once

#include "pch.h"
#include "../Core/Protocol.h"
#include "Protocol.pb.h"

#define REGIST_HANDLER(packetid)				case ePacketId::packetid: CPacketHandler::Handler_##packetid(session, header, buffer + sizeof(Protocol::PACKET_HEADER)); break
#define DEFINE_HANDLER(packetid)				static void Handler_##packetid(shared_ptr<CSession>& session, Protocol::PACKET_HEADER header, BYTE* buffer)
#define IMPL_HANDLER(packetid)					void CPacketHandler::Handler_##packetid(shared_ptr<CSession> session, Protocol::PACKET_HEADER header, BYTE* buffer)

class CSession;
class CPacketHandler
{
public:
	CPacketHandler() = default;

	static bool HandlePacket(shared_ptr<CSession> session, int32 id, BYTE* buffer, uint32 size)
	{
		// User implementation
		Protocol::PACKET_HEADER header;
		{
			if (!header.ParseFromArray(buffer, sizeof(Protocol::PACKET_HEADER)))
			{
				// Err
				return false;
			}

			// Checksum
			const auto checksum = header.checksum();
		}

		// Payload handler define
		// 'buffer' parameter in "REGIST_HANDLER" represents the actual payload length, excluding "PACKET_HEADER" length
		switch (static_cast<ePacketId>(header.id()))
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
		if (!packet.ParseFromArray(buffer, header.size()))
		{
			// Err
			return;
		}

		// TODO
	}
};