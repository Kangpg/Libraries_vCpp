#pragma once

#include "../Core/Interface.h"
#include "../Core/Types.h"
#include "../Core/Server.h"
#include <string>

class CGameServer : public CServer
{
public:
	CGameServer(const std::wstring ip, const uint16 port, const uint16 sessionCnt)
		: CServer(ip, port, sessionCnt)
	{
		
	}
	virtual ~CGameServer() = default;

public:
	bool Start()
	{
		return __super::Start();
	}
	bool End()
	{
		return __super::End();
	}

private:
};