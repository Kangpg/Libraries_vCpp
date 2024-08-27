#pragma once

#include "pch.h"

struct sHeader
{
	uint32 mSize		= 0;
	uint32 mPacketId	= 0;
};

enum class ePacketId : uint32
{
	PACKET_NONE = 0,

	PACKET_SC_CHAT,
	PACKET_CS_CHAT,
};

struct sSC_CHAT
{

};

struct sCS_CHAT
{

};