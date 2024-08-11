#pragma once

#include "pch.h"
#include "ObjectFactory.h"
#include "Session.h"
#include "Socket.h"
#include "Iocp.h"
#include "SessionManager.h"

#define dfDEFAULT_SESSION_CNT 10

class CServer
{
public:
	CServer()
		: _mSessionManager(dfDEFAULT_SESSION_CNT)
	{
		_mOverlappedList.clear();
	}
	CServer(const wstring ip, const uint16 port, const uint16 sessionCnt)
		: _mSessionManager(sessionCnt)
	{
		_mOverlappedList.clear();

		ZeroMemory(&_mAddress, sizeof(_mAddress));
		_mAddress.sin_family = AF_INET;
		_mAddress.sin_port = ::htons(port);

		::InetPtonW(AF_INET, ip.c_str(), &_mAddress.sin_addr);
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

		if (!CSocket::SetSocketOpt<bool>(_mAcceptor, SO_REUSEADDR, true))
			return false;

		if (!CSocket::Bind(_mAcceptor, _mAddress))
			return false;

		if (!CSocket::Listen(_mAcceptor, SOMAXCONN))
			return false;

		auto maxCnt = _mSessionManager.GetMaxSessionCnt();
		for (auto idx = 0; idx < maxCnt; ++idx)
		{
			auto accpetOverlapped = make_shared<COverlapped>(COverlapped::eFLAG::eAccept);
			_mOverlappedList.push_back(accpetOverlapped);

			auto session = _mSessionManager.CreateSession();

			// Reg iocp
			_mIocp.RegistHandle(reinterpret_cast<HANDLE>(session->GetSocket()));

			DWORD bytes = 0;
			if (!CSocket::AcceptEx(_mAcceptor, session->GetSocket(), session->_mRecvBuf.GetHeadPos(), 0, sizeof(SOCKADDR_IN) + 16, sizeof(SOCKADDR_IN) + 16, &bytes, static_cast<LPOVERLAPPED>(accpetOverlapped.get())))
			{
				if (WSA_IO_PENDING == ::WSAGetLastError())
				{
					// TODO : Try callback
					return false;
				}
			}
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

	vector<shared_ptr<COverlapped>>				_mOverlappedList;
	CSessionManager								_mSessionManager;
};

