#pragma once

#include "pch.h"
#include "../Core/Server.h"

class CGameServer : public CServer
{
public:
	CGameServer(const wstring ip, const uint16 port, const uint16 sessionCnt)
		: CServer(ip, port, sessionCnt)
	{
		
	}
	virtual ~CGameServer() = default;

public:
	virtual bool Start() override
	{
		return __super::Start();
	}
	virtual bool End() override
	{
		return __super::End();
	}
	
private:
};