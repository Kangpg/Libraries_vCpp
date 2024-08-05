// Libraries_vCpp.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "GameServer.h"
#include "../Core/WinNetwork.h"

#pragma comment(lib, "../x64/Debug/Core.lib")

int main()
{
	CWinNetwork net;

	CGameServer gameserver(L"127.0.0.1", 7777, 1000);

	gameserver.Start();

	return 0;
}