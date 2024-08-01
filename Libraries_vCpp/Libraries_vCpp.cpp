// Libraries_vCpp.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include "GameServer.h"

class A
{
public:
	A() {}
	int a = 1123;
};

int main()
{
	CGameServer gameserver(L"localhost", 5555, 1000);

	return 0;
}