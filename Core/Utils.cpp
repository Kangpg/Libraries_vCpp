#include "pch.h"
#include "Utils.h"

void PrintWSAError(const char* msg) {
    auto errCode = WSAGetLastError();
    wchar_t* errMsg = nullptr;

    FormatMessageW(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        errCode,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPWSTR)&errMsg,
        0,
        NULL
    );

    std::cerr << msg << L": " << (errMsg ? errMsg : L"Unknown error") << std::endl;
    if (errMsg) {
        LocalFree(errMsg);
    }
}