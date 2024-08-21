#pragma once

#include "pch.h"
#include "Singleton.h"

class CThreadManager : public  CSingletonRefLS<CThreadManager>
{
public:
	CThreadManager() = default;
	~CThreadManager();

	//void Async(function<void()> callback);

	// Async 함수의 perfect forwarding 사용 - void 리턴, void 인자
	template <typename _Func, typename = enable_if_t<is_invocable_r_v<void, _Func>>>
	void Async(_Func&& callback);
	void Join();

private:
	std::mutex						_mMutex;
#ifdef _WIN32
	vector<thread, tbb_allocator<thread>>	_mThreadList; // Movable
#else
	vector<thread>					_mThreadList;
#endif //_WIN32
};

template <typename _Func, typename>
void CThreadManager::Async(_Func&& callback) 
{
	_mThreadList.emplace_back([callback = std::forward<_Func>(callback)]() mutable 
		{
			callback();
		});
}