#pragma once

#include <memory>
#include <shared_mutex>
#include "Noncopyable.h"

template <typename _Ty>
class CSingletonRef : public CNoncopyable
{
protected:
	CSingletonRef() = default;
	~CSingletonRef() = default;

public:
	static _Ty& GetInstance()
	{
		return _mInstance;
	}

private:
	static _Ty _mInstance;
};

template <typename _Ty>
_Ty CSingletonRef<_Ty>::_mInstance;

template <typename _Ty>
class CSingletonPtr : public CNoncopyable
{
protected:
	CSingletonPtr() = default;
	~CSingletonPtr() = default;

public:
	static std::shared_ptr<_Ty> GetInstance()
	{
		std::call_once(_mFlag, []()
			{
				_mInstance = std::make_shared<_Ty>();
			});

		return _mInstance;
	}

private:
	//static std::shared_mutex	_mMutex;
	static std::once_flag		_mFlag;
	static std::shared_ptr<_Ty> _mInstance;
};

template <typename _Ty>
std::once_flag CSingletonPtr<_Ty>::_mFlag;

template <typename _Ty>
std::shared_ptr<_Ty> CSingletonPtr<_Ty>::_mInstance;

// Lock safe initialization
template <typename _Ty>
class CSingletonRefLS : public CNoncopyable
{
protected:
	CSingletonRefLS() = default;
	~CSingletonRefLS() = default;

public:
	static _Ty& GetInstance()
	{
		static _Ty _mInstance;
		return _mInstance;
	}
};

template <typename _Ty>
_Ty CSingletonRef<_Ty>::_mInstance;