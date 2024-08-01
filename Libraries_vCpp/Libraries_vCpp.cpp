// Libraries_vCpp.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

#include "../Core/ObjectFactory.h"

class A
{
public:
	A() {}
	int a = 1123;
};

int main()
{
	auto a = CObjectFactory<A, 5>::GetInstance();

	{
		auto b = a->GetObject();
		a->ReturnObject(b);
	}

	return 0;
}