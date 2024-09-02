#include "pch.h"
#include "GameServer.h"
#include "ServerSession.h"

int main()
{
	CWinNetwork net;

	auto gameserver = make_shared<CGameServer>(L"127.0.0.1", 7777, []() { return make_shared<CServerSession>(); }, 1000);

	gameserver->Start();

	CThreadManager::GetInstance().Async([&]()
		{
			while (true)
			{
				gameserver->Process();
			}
		});

	while (true)
	{

	}

	return 0;
}