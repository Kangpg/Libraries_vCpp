#include "pch.h"
#include "Server.h"

CServer::CServer()
	: _mSessionManager(dfDEFAULT_SESSION_CNT)
{
	_mOverlappedList.clear();
}

CServer::CServer(const wstring ip, const uint16 port, const uint16 sessionCnt)
	: _mSessionManager(sessionCnt)
{
	_mOverlappedList.clear();

	ZeroMemory(&_mAddress, sizeof(_mAddress));
	_mAddress.sin_family = AF_INET;
	_mAddress.sin_port = ::htons(port);

	::InetPtonW(AF_INET, ip.c_str(), &_mAddress.sin_addr);
}

CServer::~CServer()
{

}

bool CServer::Start()
{
	if (_mSock = CSocket::CreateSocket(WSA_FLAG_OVERLAPPED), _mSock == INVALID_SOCKET)
		return false;

	if (!_mIocp.RegistHandle(reinterpret_cast<HANDLE>(_mSock)))
		return false;

	LINGER linger;
	linger.l_onoff = 0;
	linger.l_linger = 0;
	if (!CSocket::SetSocketOpt<LINGER>(_mSock, SO_LINGER, linger))
		return false;

	if (!CSocket::SetSocketOpt<bool>(_mSock, SO_REUSEADDR, true))
		return false;

	if (!CSocket::Bind(_mSock, _mAddress))
		return false;

	if (!CSocket::Listen(_mSock, SOMAXCONN))
		return false;

	auto maxCnt = _mSessionManager.GetMaxSessionCnt();
	for (auto idx = 0; idx < maxCnt; ++idx)
	{
		auto session = _mSessionManager.CreateSession();

		CAcceptor* acceptEvent = new CAcceptor();
		acceptEvent->Set(session, _mSock);

		_mOverlappedList.push_back(reinterpret_cast<COverlapped*>(acceptEvent));

		// Reg iocp
		_mIocp.RegistHandle(reinterpret_cast<HANDLE>(session->GetSocket()));

		DWORD bytes = 0;
		if (!CSocket::AcceptEx(_mSock, session->GetSocket(), session->_mRecvBuf.GetHeadPos(), 0, sizeof(SOCKADDR_IN) + 16, sizeof(SOCKADDR_IN) + 16, &bytes, static_cast<LPOVERLAPPED>(acceptEvent)))
		{
			if (WSA_IO_PENDING == ::WSAGetLastError())
			{
				continue;
			}
			else
			{
				PrintWSAError("AcceptEx");
			}
		}
	}

	return true;
}

bool CServer::End()
{
	return false;
}

void CServer::Process()
{
	_mIocp.Process(10);
}