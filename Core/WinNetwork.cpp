#include "pch.h"
#include "WinNetwork.h"
#include "Socket.h"

#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

CWinNetwork::CWinNetwork()
{
	NetInit();
}

CWinNetwork::~CWinNetwork()
{
	::WSACleanup();
}

bool CWinNetwork::NetInit()
{
	WSADATA wsa;
	if (0 != ::WSAStartup(MAKEWORD(2, 2), &wsa))
	{
		//::WSAGetLastError()
		return false;
	}

	return true;
}