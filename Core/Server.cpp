#include "pch.h"
#include "Server.h"

CServer::CServer()
	: _mSessionManager(dfDEFAULT_SESSION_CNT)
{
	_mAcceptorList.clear();
}

CServer::CServer(const wstring ip, const uint16 port, const uint16 sessionCnt)
	: _mSessionManager(sessionCnt)
{
	_mAcceptorList.clear();

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
	if (_mListenSock = CSocket::CreateSocket(WSA_FLAG_OVERLAPPED), _mListenSock == INVALID_SOCKET)
		return false;

	if (!_mIocp.RegistHandle(reinterpret_cast<HANDLE>(_mListenSock)))
		return false;

	LINGER linger;
	linger.l_onoff = 0;
	linger.l_linger = 0;
	if (!CSocket::SetSocketOpt<LINGER>(_mListenSock, SO_LINGER, linger))
		return false;

	if (!CSocket::SetSocketOpt<bool>(_mListenSock, SO_REUSEADDR, true))
		return false;

	if (!CSocket::Bind(_mListenSock, _mAddress))
		return false;

	if (!CSocket::Listen(_mListenSock, SOMAXCONN))
		return false;

	auto maxCnt = _mSessionManager.GetMaxSessionCnt();
	for (auto idx = 0; idx < maxCnt; ++idx)
	{
		CAcceptor* acceptor = new CAcceptor(shared_from_this(), _mListenSock);
		_mAcceptorList.push_back(reinterpret_cast<COverlapped*>(acceptor));

		if(!acceptor->AcceptSocket())
			::runtime_error("AcceptSocket");
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