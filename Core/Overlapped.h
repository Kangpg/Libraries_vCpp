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
	explicit COverlapped(eFLAG flag = eFLAG::eNone);
	virtual ~COverlapped() = default;

	eFLAG	GetOverFlag() const;
	void	SetOverFlag(const eFLAG flag);

	virtual void PacketProcess() abstract;

protected:
	eFLAG	_mFlag = eFLAG::eNone;
};