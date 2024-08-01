#pragma once

#include "pch.h"
#include "Singleton.h"

template <typename _Ty, size_t size = 10>
class CObjectFactory : public CNoncopyable
{
public:
	CObjectFactory()
	{
		for (size_t idx = 0; idx < size; ++idx)
		{
			_mObjectList.push_back(std::make_shared<_Ty>());
		}
	}
	~CObjectFactory() noexcept = default;

	std::shared_ptr<_Ty> GetObject()
	{
		if (_mObjectList.empty())
		{
			throw std::runtime_error("Error");
		}

		auto object = _mObjectList.front();
		_mObjectList.pop_front();

		return object;
	}

	void ReturnObject(std::shared_ptr<_Ty> object)
	{
		_mObjectList.push_back(object);
	}

private:
	std::list<std::shared_ptr<_Ty>>	_mObjectList;
};

template <typename _Ty>
class CObjectFactoryLazy : public CNoncopyable
{
public:
	CObjectFactoryLazy() noexcept = default;
	~CObjectFactoryLazy() noexcept = default;

	void Init(const size_t size)
	{
		for (size_t idx = 0; idx < size; ++idx)
		{
			_mObjectList.push_back(std::make_shared<_Ty>());
		}
	}

	std::shared_ptr<_Ty> GetObject()
	{
		if (_mObjectList.empty())
		{
			throw std::runtime_error("Error");
		}

		auto object = _mObjectList.front();
		_mObjectList.pop_front();

		return object;
	}

	void ReturnObject(std::shared_ptr<_Ty> object)
	{
		_mObjectList.push_back(object);
	}

private:
	std::list<std::shared_ptr<_Ty>>	_mObjectList;
};

template <typename _Ty, size_t size = 10>
class CObjectFactorySgt : public CSingletonPtr<CObjectFactorySgt<_Ty, size>>
{
public:
	CObjectFactorySgt()
	{
		for (size_t idx = 0; idx < size; ++idx)
		{
			_mObjectList.push_back(std::make_shared<_Ty>());
		}
	}
	~CObjectFactorySgt() noexcept = default;

	std::shared_ptr<_Ty> GetObject()
	{
		if (_mObjectList.empty())
		{
			throw std::runtime_error("Error");
		}

		auto object = _mObjectList.front();
		_mObjectList.pop_front();

		return object;
	}

	void ReturnObject(std::shared_ptr<_Ty> object)
	{
		_mObjectList.push_back(object);
	}

private:
	std::list<std::shared_ptr<_Ty>>	_mObjectList;
};
