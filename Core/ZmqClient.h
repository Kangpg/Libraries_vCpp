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
	}

private:
	context_t	_mContext;
	socket_t	_mRouter;
};

