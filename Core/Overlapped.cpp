#include "pch.h"
#include "Overlapped.h"

COverlapped::COverlapped(eFLAG flag/* = eFLAG::eNone*/)
	: _mFlag(flag)
{

}

COverlapped::eFLAG COverlapped::GetOverFlag() const
{ 
	return _mFlag; 
}

void COverlapped::SetOverFlag(const eFLAG flag)
{ 
	_mFlag = flag;
}