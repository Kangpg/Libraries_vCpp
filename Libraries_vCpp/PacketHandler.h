#pragma once

#include "pch.h"

class CPacketHandler
{
protected:
	CPacketHandler() = default;

public:
	static void Init()
	{
		
	}

private:
	static unordered_map<uint16, function<void()>> _mHandlerList;
};

