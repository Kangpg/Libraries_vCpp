#pragma once

#include "pch.h"
#include "Overlapped.h"

class CIocp
{
public:
	CIocp()
	{
		_mIocp = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);
		if (_mIocp == INVALID_HANDLE_VALUE)
		{
			std::runtime_error("CreateIoCompletionPort");
		}
	}
	~CIocp() = default;

	bool RegistHandle(const HANDLE& regHandle)
	{
		return ::CreateIoCompletionPort(regHandle, _mIocp, 0, 0);
	}
	
	bool Process(const uint32 timeout)
	{
		DWORD numOfBytes = 0;
		ULONG_PTR key = 0;
		COverlapped* overlapped = nullptr;

		if (::GetQueuedCompletionStatus(_mIocp, &numOfBytes, &key, reinterpret_cast<LPOVERLAPPED*>(&overlapped), timeout))
		{

		}

		return true;
	}

private:
	HANDLE _mIocp = INVALID_HANDLE_VALUE;
};

