#pragma once

#include "pch.h"
#include "Singleton.h"

class CThreadManager : public  CSingletonRefLS<CThreadManager>
{
public:
	CThreadManager() = default;
	~CThreadManager()
	{
		Join();
	}

	void Async(function<void()> callback)
	{
		lock_guard<mutex> lock(_mMutex);

		_mThreadList.emplace_back([callback = std::move(callback)]() 
			{
				callback();
			});
	}

	void Join()
	{
		for (auto& th : _mThreadList)
		{
			if (th.joinable())
				th.join();
		}
		_mThreadList.clear();
	}

private:
	mutex					_mMutex;
	vector<thread>			_mThreadList;
};

