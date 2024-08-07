#pragma once

#include "pch.h"

#define dfDEFAULT_TASK_POOL_SIZE 2

template <size_t size = dfDEFAULT_TASK_POOL_SIZE>
class CTaskPool
{
public:
	CTaskPool();
	~CTaskPool();

	constexpr size_t GetMaxSize() const;
	constexpr size_t GetUsedSize() const;

	template <typename _Func, typename... _Args>
	future<_Invoke_result_t<decay_t<_Func>, decay_t<_Args>...>> PushTask(_Func&& func, _Args&& ... args);

private:
	void Run();

private:
	mutex							_mMutex;
	queue<function<void()>>			_mTaskQueue;
	array<thread, size>				_mManagedThreads;
	condition_variable				_mCv;
	bool							_mStop = false;
};

template <size_t size>
CTaskPool<size>::CTaskPool()
{
	for (auto& threads : _mManagedThreads)
	{
		threads = move(thread([this]()->void { Run(); }));
	}
}

template <size_t size>
CTaskPool<size>::~CTaskPool()
{
	_mStop = true;
	_mCv.notify_all();
	for (auto& threads : _mManagedThreads)
	{
		threads.join();
	}
}

template <size_t size>
inline constexpr size_t CTaskPool<size>::GetMaxSize() const
{
	return size;
}

template <size_t size>
inline constexpr size_t CTaskPool<size>::GetUsedSize() const
{
	lock_guard<mutex> lock(_mMutex);
	return _mTaskQueue.size();
}

template <size_t size>
template <typename _Func, typename... _Args>
future<_Invoke_result_t<decay_t<_Func>, decay_t<_Args>...>> CTaskPool<size>::PushTask(_Func&& func, _Args&& ... args)
{
	auto task = make_shared<packaged_task<_Invoke_result_t<decay_t<_Func>, decay_t<_Args>...>()>>(bind(forward<_Func>(func), forward<_Args>(args)...));
	auto fut = task->get_future();

	lock_guard<mutex> lock(_mMutex);
	_mTaskQueue.push([task = task]()->void { (*task)(); });

	_mCv.notify_one();

	return fut;
}

template <size_t size>
void CTaskPool<size>::Run()
{
	while (!_mStop)
	{
		unique_lock<mutex> lock(_mMutex);
		_mCv.wait(lock, [this]()->bool { return !_mTaskQueue.empty() || _mStop; });

		if (_mStop && _mTaskQueue.empty())
			return;

		auto task = move(_mTaskQueue.front());
		_mTaskQueue.pop();

		lock.unlock();
		task();
	}
}