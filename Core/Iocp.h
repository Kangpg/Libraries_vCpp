#pragma once

#include "pch.h"
#include "EventObject.h"

class CIocp
{
public:
	CIocp()
	{
		_mIocp = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);
		if (_mIocp == INVALID_HANDLE_VALUE)
		{
			runtime_error("CreateIoCompletionPort");
		}
	}
	~CIocp() = default;

	bool RegistHandle(const HANDLE& regHandle)
	{
		return ::CreateIoCompletionPort(regHandle, _mIocp, 0, 0);
	}
	
	bool Process(const uint32 timeout = INFINITE)
	{
		DWORD bytes = 0;
		ULONG_PTR key = 0;
		LPOVERLAPPED overlapped = nullptr;

		if (::GetQueuedCompletionStatus(_mIocp, &bytes, &key, &overlapped, timeout))
		{
			if (overlapped != nullptr)
			{
				auto customOverlapped = static_cast<COverlapped*>(overlapped);
				customOverlapped->PacketProcess(bytes);
			}
		}
		else
		{
			
		}

		return true;
	}

private:
	HANDLE _mIocp = INVALID_HANDLE_VALUE;
};

