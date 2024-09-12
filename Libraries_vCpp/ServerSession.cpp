#include "pch.h"
#include "ServerSession.h"

void CServerSession::OnReceived(BYTE* buffer, uint32 len)
{
	if (!CPacketHandler::HandlePacket(shared_from_this(), buffer, len))
	{
		::runtime_error("OnReceived");
	}
}