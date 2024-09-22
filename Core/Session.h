#pragma once

#include "pch.h"
#include "EventObject.h"
#include "Socket.h"
#include "StreamingBuffer.h"

class CSession : public enable_shared_from_this<CSession>
{
	friend class CAcceptor;

	enum 
	{
		eSTREAMING_BUFF_SIZE = 0x10000, // 64 kibi
	};

public:
	CSession();
	~CSession();

	void Init();
	SOCKET GetSocket() const;

	void SendPacket(::WSABUF& buf);

	void OnSessionReceived(DWORD recvBytes);
	void OnSessionConnected();

protected:
	// User override
	virtual void OnReceived(int32 id, BYTE* buffer, uint32 len)		{}
	virtual void OnConnected()		{}
	virtual void OnDisConnected()	{}
	virtual void OnSend()			{}

private:
	SOCKET									_mSock			= INVALID_SOCKET;
	SOCKADDR_IN								_mAddress		= {};

	CConnector								_mConnector;
	CDisConnector							_mDisConnector;
	CSender									_mSender;
	CReceiver								_mReceiver;

	mutable std::mutex						_mMutex;
	CStreamingBuffer<eSTREAMING_BUFF_SIZE>	_mRecvBuf;
	CStreamingBuffer<eSTREAMING_BUFF_SIZE>	_mSendBuf;
};

