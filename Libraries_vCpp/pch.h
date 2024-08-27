#pragma once

#include "../Core/Types.h"
#include "../Core/WinNetwork.h"
#include "../Core/ThreadManager.h"

#ifdef _DEBUG
#pragma comment(lib, "../x64/Debug/Core.lib")
#pragma comment(lib, "../ThirdParty/protobuf/libprotobufd.lib")
#else
#pragma comment(lib, "../ThirdParty/protobuf/libprotobuf.lib")
#endif

#include <unordered_map>
#include <functional>

using namespace std;