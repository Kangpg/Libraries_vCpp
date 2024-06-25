#pragma once

#include <mutex>
#include <queue>
#include <future>
#include <functional>
#include <thread>
#include <condition_variable>

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
	std::future<std::_Invoke_result_t<std::decay_t<_Func>, std::decay_t<_Args>...>> PushTask(_Func&& func, _Args&& ... args);

private:
	void Run();

private:
	std::mutex							_mMutex;
	std::queue<std::function<void()>>	_mTaskQueue;
	std::array<std::thread, size>		_mManagedThreads;
	std::condition_variable				_mCv;
	bool								_mStop = false;
};

template <size_t size>
CTaskPool<size>::CTaskPool()
{
	for (auto& threads : _mManagedThreads)
	{
		threads = std::move(std::thread([this]()->void { Run(); }));
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
	std::lock_guard<std::mutex> lock(_mMutex);
	return _mTaskQueue.size();
}

template <size_t size>
template <typename _Func, typename... _Args>
std::future<std::_Invoke_result_t<std::decay_t<_Func>, std::decay_t<_Args>...>> CTaskPool<size>::PushTask(_Func&& func, _Args&& ... args)
{
	auto task = std::make_shared<std::packaged_task<std::_Invoke_result_t<std::decay_t<_Func>, std::decay_t<_Args>...>()>>(std::bind(std::forward<_Func>(func), std::forward<_Args>(args)...));
	auto fut = task->get_future();

	std::lock_guard<std::mutex> lock(_mMutex);
	_mTaskQueue.push([task = task]()->void { (*task)(); });

	_mCv.notify_one();

	return fut;
}

template <size_t size>
void CTaskPool<size>::Run()
{
	while (!_mStop)
	{
		std::unique_lock<std::mutex> lock(_mMutex);
		_mCv.wait(lock, [this]()->bool { return !_mTaskQueue.empty() || _mStop; });

		if (_mStop && _mTaskQueue.empty())
			return;

		auto task = std::move(_mTaskQueue.front());
		_mTaskQueue.pop();

		lock.unlock();
		task();
	}
}