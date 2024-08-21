#pragma once

#include "pch.h"
#include "EventObject.h"
#include "Socket.h"
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
	CSession();
	~CSession();

	SOCKET GetSocket() const;

	void SendPacket(::WSABUF& buf);

	void OnReceived();
	void OnConnected();
	void OnDisconnected();

private:
	mutable std::mutex						_mMutex;
	SOCKET									_mSock			= INVALID_SOCKET;
	SOCKADDR_IN								_mAddress		= {};

	CConnector								_mConnector;
	CDisConnector							_mDIsConnector;
	CSender									_mSender;
	CReceiver								_mReceiver;

	CStreamingBuffer<eSTREAMING_BUFF_SIZE>	_mRecvBuf;
	
};

