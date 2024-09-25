#include "pch.h"
#include "ServerSession.h"

void CServerSession::OnReceived(int32 id, BYTE* buffer, uint32 len)
{
	if (!CPacketHandler::HandlePacket(shared_from_this(), id, buffer, len))
	{
		::runtime_error("OnReceived header + payload");
	}
}