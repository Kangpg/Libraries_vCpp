#include "pch.h"
#include "SessionManager.h"

CSessionManager::CSessionManager(const uint16 sessionCnt)
{
	_mSessionFactory.Init(sessionCnt);
}

shared_ptr<CSession> CSessionManager::CreateSession()
{
	// The caller needs to do a nullptr check outside the function or using runtime error
	return _mSessionFactory.GetFactoryObject();
}

void CSessionManager::DeleteSession(shared_ptr<CSession> session)
{
	_mSessionFactory.ReturnFactoryObject(session);
}

bool CSessionManager::RegistSession(shared_ptr<CSession> session)
{
	lock_guard<shared_mutex> lock(_mMutex);
	return (_mSessionList.insert({ session->GetSocket(), session })).second;
}

void CSessionManager::UnRegistSession(shared_ptr<CSession> session)
{
	lock_guard<shared_mutex> lock(_mMutex);
	_mSessionList.erase(session->GetSocket());
}

const uint16 CSessionManager::GetMaxSessionCnt() const 
{ 
	return _mSessionFactory.GetMaxObjectCnt();
}

shared_ptr<CSession> CSessionManager::GetSession(SOCKET& socket)
{
	auto itr = _mSessionList.find(socket);
	return itr != _mSessionList.end() ? itr->second : shared_ptr<CSession>();
}