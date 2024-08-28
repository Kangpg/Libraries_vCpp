#pragma once

#include "pch.h"
#include "Session.h"

class CSessionManager
{
public:
	CSessionManager(const uint16 sessionCnt, function<shared_ptr<CSession>()> func);

	shared_ptr<CSession>	CreateSession();
	void					DeleteSession(shared_ptr<CSession> session);

	const uint16			GetMaxSessionCnt() const;

private:
	mutable shared_mutex	_mMutex;

#ifdef _WIN32
	list<shared_ptr<CSession>, tbb_allocator<shared_ptr<CSession>>>		_mSessionList;
#else
	list<shared_ptr<CSession>>											_mSessionList;
#endif //_WIN32

	uint16					_mMaxSessionCnt = 0;
};