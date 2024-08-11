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
			runtime_error("CreateIoCompletionPort");
		}
	}
	~CIocp() = default;

	bool RegistHandle(const HANDLE& regHandle)
	{
		return ::CreateIoCompletionPort(regHandle, _mIocp, reinterpret_cast<ULONG_PTR>(regHandle), 0);
	}
	
	bool Process(const uint32 timeout)
	{
		DWORD numOfBytes = 0;
		ULONG_PTR key = 0;
		COverlapped* overlapped = nullptr;

		if (::GetQueuedCompletionStatus(_mIocp, &numOfBytes, &key, reinterpret_cast<LPOVERLAPPED*>(&overlapped), timeout))
		{
			// TODO : iocp 이벤트 객체를 session, acceptor 둘다 상속받게 수정필요
			switch (overlapped->GetOverFlag())
			{
			case COverlapped::eFLAG::eConnect:
				break;
			case COverlapped::eFLAG::eDisconnect:
				break;
			case COverlapped::eFLAG::eSend:
				break;
			case COverlapped::eFLAG::eReceive:
				break;
			case COverlapped::eFLAG::eAccept:
				break;
			default:
				break;
			}
		}

		return true;
	}

private:
	HANDLE _mIocp = INVALID_HANDLE_VALUE;
};

