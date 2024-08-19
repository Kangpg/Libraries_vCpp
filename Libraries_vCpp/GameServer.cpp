#include "pch.h"
#include "GameServer.h"

int main()
{
	CWinNetwork net;

	CGameServer gameserver(L"127.0.0.1", 7777, 1000);

	gameserver.Start();

	CThreadManager::GetInstance().Async([&]()
		{
			while (true)
			{
				gameserver.Process();
			}
		});

	while (true)
	{

	}

	return 0;
}