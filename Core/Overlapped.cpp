#include "pch.h"
#include "Overlapped.h"

COverlapped::COverlapped(eFLAG flag/* = eFLAG::eNone*/)
	: _mFlag(flag)
{
	Init();
}

void COverlapped::Init()
{
	OVERLAPPED::hEvent = 0;
	OVERLAPPED::Internal = 0;
	OVERLAPPED::InternalHigh = 0;
	OVERLAPPED::Offset = 0;
	OVERLAPPED::OffsetHigh = 0;
}

COverlapped::eFLAG COverlapped::GetOverFlag() const
{ 
	return _mFlag; 
}

void COverlapped::SetOverFlag(const eFLAG flag)
{ 
	_mFlag = flag;
}