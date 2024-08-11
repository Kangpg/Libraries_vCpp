#include "pch.h"
#include "Socket.h"
#include "Utils.h"

LPFN_CONNECTEX		        CSocket::ConnectEx              = nullptr;
LPFN_DISCONNECTEX	        CSocket::DisconnectEx           = nullptr;
LPFN_ACCEPTEX		        CSocket::AcceptEx               = nullptr;
LPFN_GETACCEPTEXSOCKADDRS	CSocket::GetAcceptExSockAddrs   = nullptr;
LPFN_TRANSMITFILE			CSocket::TransmitFile           = nullptr;

SOCKET CSocket::CreateSocket(DWORD ioflag)
{
    SOCKET sock = INVALID_SOCKET;
    if (sock = ::WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, ioflag), INVALID_SOCKET == sock)
    {
        PrintWSAError("CreateSocket");
        return INVALID_SOCKET;
    }

    return sock;
}

void CSocket::CloseSocket(SOCKET& sock)
{
    if (INVALID_SOCKET != sock)
        ::closesocket(sock);

    sock = INVALID_SOCKET;
}

bool CSocket::Bind(SOCKET& sock, const wchar_t* ip, const uint16 port)
{
    if (sock == INVALID_SOCKET)
        return false;

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = ::htons(port);

    auto ret = ::InetPtonW(AF_INET, ip, &address.sin_addr);
    switch (ret)
    {
    case -1:
        PrintWSAError("InetPtonW");
        return false;
    case 0:
        runtime_error("InetPtonW invalid address");
        return false;
    }

    if (SOCKET_ERROR == ::bind(sock, reinterpret_cast<const sockaddr*>(&address), sizeof(sockaddr_in)))
    {
        PrintWSAError("Bind");
        return false;
    }

    return true;
}

bool CSocket::Bind(SOCKET& sock, SOCKADDR_IN address)
{
    if (sock == INVALID_SOCKET)
        return false;

    auto ret = ::bind(sock, reinterpret_cast<const sockaddr*>(&address), sizeof(sockaddr_in));
    if (SOCKET_ERROR == ret)
    {
        PrintWSAError("Bind");
        return false;
    }

    return true;
}

bool CSocket::Listen(SOCKET& sock, const int blog/*= SOMAXCONN*/)
{
    if (SOCKET_ERROR == ::listen(sock, blog))
    {
        PrintWSAError("Listen");
        return false;
    }

    return true;
}