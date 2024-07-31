#pragma once

#include "Interface.h"
#include "Types.h"
#include <string>

class CGameServer : public CInterface
{
public:
	CGameServer(const std::wstring ip, const uint16 port)
	{

	}
	virtual ~CGameServer() = default;

public:
	virtual bool Start() override
	{

	}
	virtual bool End() override
	{

	}

private:
	
};

