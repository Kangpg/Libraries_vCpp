#pragma once

#include "Singleton.h"

class CWinNetwork : public CSingletonRef<CWinNetwork>
{
public:
	CWinNetwork();
	~CWinNetwork();

	bool NetInit();
};