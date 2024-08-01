#pragma once

#include "Socket.h"

std::string GetWSAErrorMessage(int errorCode) {
    char* messageBuffer = nullptr;

    FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        nullptr,
        errorCode,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPSTR)&messageBuffer,
        0,
        nullptr
    );

    std::string message(messageBuffer);

    LocalFree(messageBuffer);

    return message;
}

class CAcceptor
{
public:
	CAcceptor() = default;
	~CAcceptor() = default;

	bool Accept()
	{
		if (_mSocket = CSocket::CreateSocket(WSA_FLAG_OVERLAPPED), _mSocket == INVALID_SOCKET)
		{
			throw std::runtime_error(GetWSAErrorMessage(::WSAGetLastError()));
		}

        if (!CSocket::Bind(_mSocket, L"localhost", 5555))
        {
            throw std::runtime_error(GetWSAErrorMessage(::WSAGetLastError()));
        }

        if (!CSocket::Listen(_mSocket, SOMAXCONN))
        {
            throw std::runtime_error(GetWSAErrorMessage(::WSAGetLastError()));
        }

		return true;
	}

private:
	SOCKET _mSocket = INVALID_SOCKET;
};

