#pragma once

#include "pch.h"
#include "Overlapped.h"

class CSession;

class CServer;
class CAcceptor : public COverlapped
{
public:
	CAcceptor();
	CAcceptor(shared_ptr<CServer> server, SOCKET listenSocket);

	void			Init(shared_ptr<CSession> session);
	virtual void	PacketProcess(DWORD recvBytes) override;

	bool			RegistSocket(SOCKET socket);
	bool			AcceptSocket();

private:
	shared_ptr<CServer>		_mServer;
	shared_ptr<CSession>	_mSession;
	SOCKET					_mListenSock = INVALID_SOCKET;
};

class CConnector : public COverlapped
{
public:
	CConnector();

	void			Init(shared_ptr<CSession> session);
	virtual void	PacketProcess(DWORD recvBytes) override;

private:
	shared_ptr<CSession>	_mSession;
};

class CDisConnector : public COverlapped
{
public:
	CDisConnector();

	void			Init(shared_ptr<CSession> session);
	virtual void	PacketProcess(DWORD recvBytes) override;

private:
	shared_ptr<CSession>	_mSession;
};

class CSender : public COverlapped
{
public:
	CSender();

	void			Init(shared_ptr<CSession> session);
	virtual void	PacketProcess(DWORD recvBytes) override;

private:
	shared_ptr<CSession>	_mSession;
};

class CReceiver : public COverlapped
{
public:
	CReceiver();

	void			Init(shared_ptr<CSession> session);
	virtual void	PacketProcess(DWORD recvBytes) override;

private:
	shared_ptr<CSession>	_mSession;
};