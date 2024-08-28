#pragma once

#include "../Core/Session.h"

class CServerSession : public CSession
{
public:
	CServerSession() = default;
	virtual ~CServerSession() = default;

protected:
	virtual void OnConnected() {}
	virtual void OnDisConnected() {}
	virtual void OnReceived() {}
	virtual void OnSend() {}
};

