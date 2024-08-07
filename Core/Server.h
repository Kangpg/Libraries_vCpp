#pragma once

#include "pch.h"
#include "ObjectFactory.h"
#include "Session.h"
#include "Socket.h"
#include "Iocp.h"

#define dfDEFAULT_SESSION_CNT = 100;

class CServer
{
public:
	CServer()
	{
		_mOverlappedList.clear();
	}
	CServer(const wstring ip, const uint16 port, const uint16 sessionCnt)
	{
		_mOverlappedList.clear();

		ZeroMemory(&_mAddress, sizeof(_mAddress));
		_mAddress.sin_family = AF_INET;
		_mAddress.sin_port = ::htons(port);

		::InetPtonW(AF_INET, ip.c_str(), &_mAddress.sin_addr);

		_mSessionFactory.Init(static_cast<size_t>(sessionCnt));
	}
	~CServer() = default;

public:
	virtual bool Start()
	{
		if (_mAcceptor = CSocket::CreateSocket(WSA_FLAG_OVERLAPPED), _mAcceptor == INVALID_SOCKET)
			return false;

		if (!_mIocp.RegistHandle(reinterpret_cast<HANDLE>(_mAcceptor)))
			return false;

		LINGER linger;
		linger.l_onoff = 0;
		linger.l_linger = 0;
		if (!CSocket::SetSocketOpt<LINGER>(_mAcceptor, SO_LINGER, linger))
			return false;

		if (!CSocket::Bind(_mAcceptor, _mAddress))
			return false;

		if (!CSocket::Listen(_mAcceptor, SOMAXCONN))
			return false;

		auto maxCnt = _mSessionFactory.GetMaxObjectCnt();
		for (auto idx = 0; idx < maxCnt; ++idx)
		{
			auto accpetOverlapped = make_shared<COverlapped>(COverlapped::eFLAG::eAccept);
			_mOverlappedList.push_back(accpetOverlapped);

			// TODO
		}

		return true;
	}

	virtual bool End()
	{
		return false;
	}

private:
	SOCKADDR_IN									_mAddress = {};
	SOCKET										_mAcceptor = INVALID_SOCKET;
	CIocp										_mIocp;

	CObjectFactoryLazy<CSession>				_mSessionFactory;
	vector<shared_ptr<COverlapped>>				_mOverlappedList;
};

