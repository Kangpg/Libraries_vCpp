#pragma once

#include "pch.h"
#include "session.h"
#include "Singleton.h"
#include "ObjectFactory.h"

class CSessionManager
{
public:
	CSessionManager(const uint16 sessionCnt)
	{
		_mSessionFactory.Init(sessionCnt);
	}
	~CSessionManager() = default;

	shared_ptr<CSession> CreateSession()
	{
		// The caller needs to do a nullptr check outside the function or using runtime error
		return _mSessionFactory.GetFactoryObject();
	}

	void DeleteSession(shared_ptr<CSession> session)
	{
		_mSessionFactory.ReturnFactoryObject(session);
	}

	bool RegistSession(shared_ptr<CSession> session)
	{
		lock_guard<shared_mutex> lock(_mMutex);
		return (_mSessionList.insert({ session->GetSocket(), session })).second;
	}

	void UnRegistSession(shared_ptr<CSession> session)
	{
		lock_guard<shared_mutex> lock(_mMutex);
		_mSessionList.erase(session->GetSocket());
	}

	const uint16 GetMaxSessionCnt() const { return _mSessionFactory.GetMaxObjectCnt(); }

	shared_ptr<CSession> GetSession(SOCKET& socket)
	{
		auto itr = _mSessionList.find(socket);
		return itr != _mSessionList.end() ? itr->second : shared_ptr<CSession>();
	}

private:
	shared_mutex								_mMutex;
	unordered_map<SOCKET, shared_ptr<CSession>> _mSessionList;

	CObjectFactoryLazy<CSession>				_mSessionFactory;
};

