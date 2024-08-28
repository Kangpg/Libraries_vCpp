#include "pch.h"
#include "SessionManager.h"

CSessionManager::CSessionManager(const uint16 sessionCnt, function<shared_ptr<CSession>()> func)
	: _mMaxSessionCnt(sessionCnt)
{
	for (auto idx = 0; idx < _mMaxSessionCnt; ++idx)
	{
		shared_ptr<CSession> session = func();
		_mSessionList.push_back(session);
	}
}

shared_ptr<CSession> CSessionManager::CreateSession()
{
	if (!_mSessionList.empty())
	{
		auto session = _mSessionList.front();
		_mSessionList.pop_front();
		return session;
	}

	// The caller needs to do a nullptr check outside the function or using runtime error
	return shared_ptr<CSession>();
}

void CSessionManager::DeleteSession(shared_ptr<CSession> session)
{
	_mSessionList.push_back(session);
}

const uint16 CSessionManager::GetMaxSessionCnt() const
{
	return _mMaxSessionCnt;
}