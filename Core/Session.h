#pragma once

#include "pch.h"
#include "Acceptor.h"
#include "StreamingBuffer.h"

class CSndBuffer
{
public:
	CSndBuffer() = default;
	~CSndBuffer() = default;

private:
	::WSABUF _mBuff;
};

class CSession
{
	friend class CServer;

	enum 
	{
		eSTREAMING_BUFF_SIZE = 0x10000, // 64 kibi
	};

public:
	CSession() = default;
	virtual ~CSession() = default;

	SOCKET GetSocket() const { return _mSock; }

	void SendPacket(::WSABUF& buf)
	{
		{
			lock_guard<mutex> lock(_mMutex);

			/*auto ret = ::WSASend(_mSock, &buf, buf.len, )*/
		}
	}

	void OnReceived()
	{

	}

private:
	mutex									_mMutex;
	SOCKET									_mSock = INVALID_SOCKET;

	CConnector								_mConnector;
	CDisConnector							_mDIsConnector;
	CSender									_mSender;
	CReceiver								_mReceiver;

	CStreamingBuffer<eSTREAMING_BUFF_SIZE>	_mRecvBuf;
	
};

