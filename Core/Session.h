#pragma once

#include "pch.h"
#include "StreamingBuffer.h"
#include "Overlapped.h"

class CSndBuffer
{
public:
	CSndBuffer() = default;
	~CSndBuffer() = default;

private:
	::WSABUF _mBuff;
};

class CSession : public COverlapped
{
	enum 
	{
		eSTREAMING_BUFF_SIZE = 0x10000, // 64 kibi
	};

public:
	CSession() = default;
	virtual ~CSession() = default;

	void SendPacket(::WSABUF& buf)
	{
		{
			lock_guard<mutex> lock(_mMutex);

			/*auto ret = ::WSASend(_mSock, &buf, buf.len, )*/
		}
	}

private:
	mutex									_mMutex;
	SOCKET									_mSock = INVALID_SOCKET;

	CStreamingBuffer<eSTREAMING_BUFF_SIZE>	_mRecvBuf;
	
};

