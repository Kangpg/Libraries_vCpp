#pragma once

#include "pch.h"
#include "../Core/Server.h"

class CGameServer final : public CServer
{
public:
	CGameServer(const wstring ip, const uint16 port, function<shared_ptr<CSession>()> func, const uint16 sessionCnt)
		: CServer(ip, port, func, sessionCnt)
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