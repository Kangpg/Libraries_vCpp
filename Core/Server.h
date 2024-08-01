#pragma once

#include "pch.h"
#include "Interface.h"
#include "ObjectFactory.h"
#include "Session.h"
#include "Acceptor.h"
#include "Socket.h"

#define dfDEFAULT_SESSION_CNT = 100;

class CServer : public CInterface
{
public:
	CServer(const std::wstring ip, const uint16 port, const uint16 sessionCnt)
	{
		ZeroMemory(&_mAddress, sizeof(_mAddress));
		_mAddress.sin_family = AF_INET;
		_mAddress.sin_port = ::htons(port);

		::InetPtonW(AF_INET, ip.c_str(), &_mAddress.sin_addr);

		_mSessionFactory.Init(static_cast<size_t>(sessionCnt));
	}
	~CServer() = default;

public:
	virtual bool Start() override
	{
		if (_mAcceptor = CSocket::CreateSocket(WSA_FLAG_OVERLAPPED), _mAcceptor = INVALID_SOCKET)
			// Log
			return false;

		LINGER linger;
		linger.l_onoff = 0;
		linger.l_linger = 0;
		if (!CSocket::SetSocketOpt<LINGER>(_mAcceptor, SO_LINGER, linger))
			// Log
			return false;

		if (!CSocket::Bind(_mAcceptor, _mAddress))
			// Log
			return false;

		if (!CSocket::Listen(_mAcceptor, SOMAXCONN))
			// Log
			return false;

		// AcceptEx
	}

	virtual bool End() override
	{

	}

private:
	SOCKADDR_IN						_mAddress = {};
	SOCKET							_mAcceptor = INVALID_SOCKET;

	CObjectFactoryLazy<CSession>	_mSessionFactory;
};

