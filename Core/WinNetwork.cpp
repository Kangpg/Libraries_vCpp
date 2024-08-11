#include "pch.h"
#include "WinNetwork.h"
#include "Socket.h"

CWinNetwork::CWinNetwork()
{
	NetInit();

	auto dummy = CSocket::CreateSocket(WSA_FLAG_OVERLAPPED);

	auto _lamIoctl = [dummy = dummy](GUID inbuf, LPVOID* outbuf)->bool
		{
			DWORD bytes = 0;
			return SOCKET_ERROR != ::WSAIoctl(dummy, SIO_GET_EXTENSION_FUNCTION_POINTER, &inbuf, sizeof(inbuf), outbuf, sizeof(*outbuf), &bytes, NULL, NULL);
		};

	if (!_lamIoctl(WSAID_CONNECTEX, reinterpret_cast<LPVOID*>(&CSocket::ConnectEx))) { runtime_error("ConnectEx WSAIoctl"); }
	if (!_lamIoctl(WSAID_DISCONNECTEX, reinterpret_cast<LPVOID*>(&CSocket::DisconnectEx))) { runtime_error("DisConnectEx WSAIoctl"); }
	if (!_lamIoctl(WSAID_ACCEPTEX, reinterpret_cast<LPVOID*>(&CSocket::AcceptEx))) { runtime_error("AcceptEx WSAIoctl"); }
	if (!_lamIoctl(WSAID_GETACCEPTEXSOCKADDRS, reinterpret_cast<LPVOID*>(&CSocket::GetAcceptExSockAddrs))) { runtime_error("GetAcceptExSockAddrs WSAIoctl"); }
	if (!_lamIoctl(WSAID_TRANSMITFILE, reinterpret_cast<LPVOID*>(&CSocket::TransmitFile))) { runtime_error("TransmitFile WSAIoctl"); }

	CSocket::CloseSocket(dummy);
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