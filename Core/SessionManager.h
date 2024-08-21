#pragma once

#include "pch.h"
#include "Session.h"
#include "ObjectFactory.h"

class CSessionManager
{
public:
	CSessionManager(const uint16 sessionCnt);

	shared_ptr<CSession>	CreateSession();

	void					DeleteSession(shared_ptr<CSession> session);
	bool					RegistSession(shared_ptr<CSession> session);
	void					UnRegistSession(shared_ptr<CSession> session);

	const uint16			GetMaxSessionCnt() const;
	shared_ptr<CSession>	GetSession(SOCKET& socket);

private:
	mutable shared_mutex	_mMutex;

#ifdef _WIN32
	unordered_map<SOCKET, shared_ptr<CSession>
		, hash<SOCKET>, equal_to<SOCKET>
		, tbb_allocator<pair<const SOCKET, shared_ptr<CSession>>>>	_mSessionList;
#else
	unordered_map<SOCKET, shared_ptr<CSession>>					_mSessionList;
#endif //_WIN32

	CObjectFactoryLazy<CSession>				_mSessionFactory;
};

