#pragma once

#include "pch.h"
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
	static shared_ptr<_Ty> GetInstance()
	{
		call_once(_mFlag, []()
			{
				_mInstance = s:make_shared<_Ty>();
			});

		return _mInstance;
	}

private:
	//static shared_mutex	_mMutex;
	static once_flag		_mFlag;
	static shared_ptr<_Ty> _mInstance;
};

template <typename _Ty>
once_flag CSingletonPtr<_Ty>::_mFlag;

template <typename _Ty>
shared_ptr<_Ty> CSingletonPtr<_Ty>::_mInstance;

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