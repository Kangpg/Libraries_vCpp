#include "Types.h"

#ifndef NOMINMAX 
#define NOMINMAX
#endif

#include <winsock2.h>
#include <Windows.h>
#include <memory>
#include <iostream>
#include <cstddef>
#include <functional>
#include <MSWSock.h>
#include <Ws2tcpip.h>
#include <type_traits>
#include <utility>

#pragma comment(lib, "ws2_32.lib")

#include <unordered_map>
#include <unordered_set>
#include <string>
#include <shared_mutex>
#include <mutex>
#include <queue>
#include <deque>
#include <future>
#include <thread>
#include <condition_variable>
#include <vector>

#ifdef _WIN32
#include "oneapi/tbb.h"
#pragma comment(lib, "tbbmalloc")

#define __TBB_NO_IMPLICIT_LINKAGE 1
#define __TBBMALLOC_NO_IMPLICIT_LINKAGE 1

#endif

using namespace std;
using namespace tbb;