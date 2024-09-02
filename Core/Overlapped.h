#pragma once

#include "pch.h"

class COverlapped abstract : public ::OVERLAPPED
{
public:
	enum class eFLAG
	{
		eNone = 0,

		eConnect,
		eDisconnect,
		eSend,
		eReceive,
		eAccept,

		eEnd,
	};

public:
	explicit		COverlapped(eFLAG flag = eFLAG::eNone);

	void			Init();

	eFLAG			GetOverFlag() const;
	void			SetOverFlag(const eFLAG flag);

	virtual void	PacketProcess(DWORD recvBytes) abstract;

protected:
	eFLAG					_mFlag = eFLAG::eNone;
};