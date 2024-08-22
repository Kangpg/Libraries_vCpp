#pragma once

#include "pch.h"
#include "Socket.h"
#include "Iocp.h"
#include "SessionManager.h"
#include "Utils.h"

#define dfDEFAULT_SESSION_CNT 10

class CServer : public enable_shared_from_this<CServer>
{
	friend class CAcceptor;

public:
	CServer();
	CServer(const wstring ip, const uint16 port, const uint16 sessionCnt);
	~CServer();

public:
	virtual bool	Start();
	virtual bool	End();

	void			Process();

private:
	SOCKADDR_IN									_mAddress = {};
	SOCKET										_mListenSock = INVALID_SOCKET;
	CIocp										_mIocp;

#ifdef _WIN32
	vector<COverlapped*, tbb_allocator<COverlapped*>>	_mAcceptorList;
#else
	vector<COverlapped*>						_mOverlappedList;
#endif //_WIN32
	CSessionManager								_mSessionManager;
};

