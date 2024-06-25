#pragma once

#include "Types.h"
#include <string>
#include <winsock2.h>
#include <MSWSock.h>
#pragma comment(lib, "ws2_32.lib")

class CSocket abstract
{
public:
	static LPFN_ACCEPTEX				AcceptEx;
	static LPFN_CONNECTEX				ConnectEx;
	static LPFN_DISCONNECTEX			DisconnectEx;
	static LPFN_GETACCEPTEXSOCKADDRS	GetAcceptExSockAddrs;
	static LPFN_TRANSMITFILE			TransmitFile;

	enum class eSOCKET_PROTO : int
	{
		TCP = 0,
		UDP,
	};

public:
	static void		SocketMsApiInit();

	static SOCKET	CreateSocket(DWORD ioflag = 0);
	static void		CloseSocket(SOCKET& sock);
	
	template <typename _Opt>
	static bool		SetSocketOpt(SOCKET& sock, int32 optNm, _Opt opt);

	static bool		Bind(SOCKET& sock, const wchar_t* ip, const uint16 port);
	static bool		Listen(SOCKET& sock, const int blog = SOMAXCONN);

};

template<typename _Opt>
inline bool CSocket::SetSocketOpt(SOCKET& sock, int32 optNm, _Opt opt)
{
	return ::setsockopt(sock, SOL_SOCKET, optNm, reinterpret_cast<const char*>(&opt), sizeof(_Opt));
}