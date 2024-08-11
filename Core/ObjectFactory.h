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
			_mObjectList.push_back(make_shared<_Ty>());
		}
	}
	~CObjectFactory() noexcept = default;

	shared_ptr<_Ty> GetFactoryObject()
	{
		if (_mObjectList.empty())
		{
			throw runtime_error("Error");
		}

		auto object = _mObjectList.front();
		_mObjectList.pop_front();

		return object;
	}

	void ReturnFactoryObject(shared_ptr<_Ty> object)
	{
		_mObjectList.push_back(object);
	}

private:
	list<shared_ptr<_Ty>>	_mObjectList;
};

template <typename _Ty>
class CObjectFactoryLazy : public CNoncopyable
{
public:
	CObjectFactoryLazy() noexcept = default;
	~CObjectFactoryLazy() noexcept = default;

	void Init(const uint32 size)
	{
		_mMaxObjectCnt = size;

		for (auto idx = 0; idx < static_cast<int>(size); ++idx)
		{
			_mObjectList.push_back(make_shared<_Ty>());
		}
	}

	shared_ptr<_Ty> GetFactoryObject()
	{
		if (_mObjectList.empty())
		{
			throw runtime_error("Error");
		}

		auto object = _mObjectList.front();
		_mObjectList.pop_front();

		return object;
	}

	void ReturnFactoryObject(shared_ptr<_Ty> object)
	{
		_mObjectList.push_back(object);
	}

	uint32 GetMaxObjectCnt() const { return _mMaxObjectCnt; }

private:
	list<shared_ptr<_Ty>>	_mObjectList;
	uint32					_mMaxObjectCnt = 0;
};

template <typename _Ty, size_t size = 10>
class CObjectFactorySgt : public CSingletonPtr<CObjectFactorySgt<_Ty, size>>
{
public:
	CObjectFactorySgt()
	{
		for (size_t idx = 0; idx < size; ++idx)
		{
			_mObjectList.push_back(make_shared<_Ty>());
		}
	}
	~CObjectFactorySgt() noexcept = default;

	shared_ptr<_Ty> GetFactoryObject()
	{
		if (_mObjectList.empty())
		{
			throw runtime_error("Error");
		}

		auto object = _mObjectList.front();
		_mObjectList.pop_front();

		return object;
	}

	void ReturnFactoryObject(shared_ptr<_Ty> object)
	{
		_mObjectList.push_back(object);
	}

private:
	list<shared_ptr<_Ty>>	_mObjectList;
};
