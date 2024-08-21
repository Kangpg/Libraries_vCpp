#include "pch.h"
#include "ThreadManager.h"

CThreadManager::~CThreadManager()
{
	Join();
}

//void CThreadManager::Async(function<void()> callback)
//{
//	lock_guard<mutex> lock(_mMutex);
//
//	_mThreadList.emplace_back([callback = std::move(callback)]() mutable
//		{
//			callback();
//		});
//}

void CThreadManager::Join()
{
	for (auto& th : _mThreadList)
	{
		if (th.joinable())
			th.join();
	}
	_mThreadList.clear();
}