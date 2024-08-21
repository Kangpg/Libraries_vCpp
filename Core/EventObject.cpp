#include "pch.h"
#include "EventObject.h"

CConnector::CConnector()
	: COverlapped(COverlapped::eFLAG::eConnect)
{

}

void CConnector::PacketProcess()
{

}

CDisConnector::CDisConnector()
	: COverlapped(COverlapped::eFLAG::eDisconnect) 
{

}

void CDisConnector::PacketProcess()
{

}

CSender::CSender()
	: COverlapped(COverlapped::eFLAG::eSend)
{

}

void CSender::PacketProcess()
{

}

CReceiver::CReceiver() 
	: COverlapped(COverlapped::eFLAG::eReceive) 
{

}

void CReceiver::PacketProcess()
{

}