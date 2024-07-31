#include "pch.h"
#include "Socket.h"

#include <WS2tcpip.h>

LPFN_ACCEPTEX				CSocketUtil::AcceptEx               = nullptr;
LPFN_CONNECTEX				CSocketUtil::ConnectEx              = nullptr;
LPFN_DISCONNECTEX			CSocketUtil::DisconnectEx           = nullptr;
LPFN_GETACCEPTEXSOCKADDRS	CSocketUtil::GetAcceptExSockAddrs   = nullptr;
LPFN_TRANSMITFILE			CSocketUtil::TransmitFile           = nullptr;

void CSocketUtil::SocketMsApiInit()
{
    SOCKET dsock = CreateSocket(WSA_FLAG_OVERLAPPED);
}

SOCKET CSocketUtil::CreateSocket(DWORD ioflag/*= 0*/)
{
    SOCKET sock = INVALID_SOCKET;
    if (sock = ::WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, ioflag), INVALID_SOCKET == sock)
    {
        //::WSAGetLastError()
    }

    return sock;
}

void CSocketUtil::CloseSocket(SOCKET& sock)
{
    if (INVALID_SOCKET != sock)
        ::closesocket(sock);

    sock = INVALID_SOCKET;
}

bool CSocketUtil::Bind(SOCKET& sock, const wchar_t* ip, const uint16 port)
{
    if (sock == INVALID_SOCKET)
        return false;

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = ::htons(port);

    ::InetPtonW(AF_INET, ip, &address.sin_addr);

    if (SOCKET_ERROR == ::bind(sock, reinterpret_cast<const sockaddr*>(&address.sin_addr), sizeof(sockaddr)))
    {
        // WSAGetLastError()
        return false;
    }

    return true;
}

bool CSocketUtil::Listen(SOCKET& sock, const int blog/*= SOMAXCONN*/)
{
    if (SOCKET_ERROR == ::listen(sock, blog))
    {
        // WSAGetLastError()
        return false;
    }

    return true;
}
