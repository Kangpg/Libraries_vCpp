#pragma once

#include "pch.h"
#include "zmq.hpp"

using namespace zmq;

#define dfDEFAULT_CONTEXT_CNT 1

class CZmqServer
{
public:
	CZmqServer(string zmqAddress, uint32 contextCnt = dfDEFAULT_CONTEXT_CNT)
		: _mContext(contextCnt), _mDealer(_mContext, socket_type::router)
	{
		_mDealer.bind(zmqAddress.c_str());

		_mThread = thread(&CZmqServer::ZmqHandler, this, &_mContext);
	}

	virtual ~CZmqServer()
	{
		if(_mThread.joinable())
			_mThread.join();
	}

	virtual void ZmqHandler(context_t& context)
	{
		while (true)
		{
			message_t msg;
			_mDealer.recv(msg, recv_flags::none);
		}
	}

private:
	context_t	_mContext;
	socket_t	_mDealer;
	thread		_mThread;
};

