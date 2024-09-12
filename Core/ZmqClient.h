#pragma once

#include "pch.h"
#include "zmq.hpp"

using namespace zmq;

#define dfDEFAULT_CONTEXT_CNT 1

class CZmqClient
{
public:
	CZmqClient(string zmqAddress, uint32 contextCnt = dfDEFAULT_CONTEXT_CNT)
		: _mContext(contextCnt), _mRouter(_mContext, socket_type::dealer)
	{
		_mRouter.connect(zmqAddress.c_str());

		_mThread = thread(&CZmqClient::ZmqHandler, this, &_mContext);
	}

	virtual ~CZmqClient()
	{
		if (_mThread.joinable())
			_mThread.join();
	}

	virtual void ZmqHandler(context_t& context)
	{
		while (true)
		{
			message_t msg;
			_mRouter.recv(msg, recv_flags::none);
		}
	}

private:
	context_t	_mContext;
	socket_t	_mRouter;
	thread		_mThread;
};

