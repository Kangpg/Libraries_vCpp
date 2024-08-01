#pragma once

#include "pch.h"

class CSocketUtil abstract
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
inline bool CSocketUtil::SetSocketOpt(SOCKET& sock, int32 optNm, _Opt opt)
{
	return ::setsockopt(sock, SOL_SOCKET, optNm, reinterpret_cast<const char*>(&opt), sizeof(_Opt));
}

class CSocket
{
public:
	CSocket(DWORD ioflag = 0)
	{
		if (_mSocket = ::WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, ioflag), _mSocket == INVALID_SOCKET)
		{
			throw std::runtime_error("Socket constructor error : " + std::to_string(::WSAGetLastError()));
		}
	}
	~CSocket()
	{
		if (_mSocket != INVALID_SOCKET)
			closesocket(_mSocket);
	}

	SOCKET GetSocket() const { return _mSocket; }

private:
	SOCKET _mSocket = INVALID_SOCKET;
};