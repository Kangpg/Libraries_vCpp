#pragma once

//std::string GetWSAErrorMessage(int errorCode) {
//    char* messageBuffer = nullptr;
//
//    FormatMessageA(
//        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
//        nullptr,
//        errorCode,
//        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
//        (LPSTR)&messageBuffer,
//        0,
//        nullptr
//    );
//
//    std::string message(messageBuffer);
//
//    LocalFree(messageBuffer);
//
//    return message;
//}

class CWinNetwork
{
public:
	CWinNetwork();
	~CWinNetwork();

	static bool NetInit();
};