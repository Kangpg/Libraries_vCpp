#pragma once

#include "Singleton.h"

class CWinNetwork : public CSingletonRef<CWinNetwork>
{
public:
	CWinNetwork() = default;
	~CWinNetwork() = default;

	bool NetInit();
};