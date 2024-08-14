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
	explicit COverlapped(eFLAG flag = eFLAG::eNone) : _mFlag(flag) {}
	virtual ~COverlapped() = default;

	eFLAG	GetOverFlag() const { return _mFlag; }
	void	SetOverFlag(const eFLAG flag) { _mFlag = flag; }

	virtual void PacketProcess() abstract;

public:
	eFLAG	_mFlag = eFLAG::eNone;
};