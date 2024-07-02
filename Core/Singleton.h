#pragma once

#include <memory>
#include <mutex>
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
class CSingletonPtr : public std::enable_shared_from_this<CSingletonPtr<_Ty>>, CNoncopyable
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
	static std::once_flag		_mFlag;
	static std::shared_ptr<_Ty> _mInstance;
};

template <typename _Ty>
std::once_flag CSingletonPtr<_Ty>::_mFlag;

template <typename _Ty>
std::shared_ptr<_Ty> CSingletonPtr<_Ty>::_mInstance;

// swap 이 가능한 포인터를 사용한 싱글톤 객체도 필요?