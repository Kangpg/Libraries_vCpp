#pragma once

#include "pch.h"
#include "Singleton.h"

/// <summary>
/// CObjectFactory class
/// </summary>
template <typename _Ty, size_t size = 10>
class CObjectFactory : public CNoncopyable
{
public:
	CObjectFactory();
	~CObjectFactory() noexcept = default;

	shared_ptr<_Ty> GetFactoryObject();
	void			ReturnFactoryObject(shared_ptr<_Ty> object);

private:
	list<shared_ptr<_Ty>>	_mObjectList;
};

template <typename _Ty, size_t size>
CObjectFactory<_Ty, size>::CObjectFactory()
{
	for (size_t idx = 0; idx < size; ++idx)
	{
		_mObjectList.push_back(make_shared<_Ty>());
	}
}

template <typename _Ty, size_t size>
shared_ptr<_Ty> CObjectFactory<_Ty, size>::GetFactoryObject()
{
	if (_mObjectList.empty())
	{
		throw runtime_error("Error");
	}

	auto object = _mObjectList.front();
	_mObjectList.pop_front();

	return object;
}

template <typename _Ty, size_t size>
void CObjectFactory<_Ty, size>::ReturnFactoryObject(shared_ptr<_Ty> object)
{
	_mObjectList.push_back(object);
}

/// <summary>
/// CObjectFactory class with lazy initialization
/// </summary>
template <typename _Ty>
class CObjectFactoryLazy : public CNoncopyable
{
public:
	CObjectFactoryLazy()	noexcept = default;
	~CObjectFactoryLazy()	noexcept = default;

	void			Init(const uint32 size);
	shared_ptr<_Ty> GetFactoryObject();
	void			ReturnFactoryObject(shared_ptr<_Ty> object);
	uint32			GetMaxObjectCnt() const;

private:

#ifdef _WIN32
	list<shared_ptr<_Ty>, tbb_allocator<shared_ptr<_Ty>>>	_mObjectList;
#else
	list<shared_ptr<_Ty>>					_mObjectList;
#endif //_WIN32
	uint32									_mMaxObjectCnt = 0;
};

template <typename _Ty>
void CObjectFactoryLazy<_Ty>::Init(const uint32 size)
{
	_mMaxObjectCnt = size;

	for (auto idx = 0; idx < static_cast<int>(size); ++idx)
	{
		_mObjectList.push_back(make_shared<_Ty>());
	}
}

template <typename _Ty>
shared_ptr<_Ty> CObjectFactoryLazy<_Ty>::GetFactoryObject()
{
	if (_mObjectList.empty())
		throw runtime_error("Error");

	auto object = _mObjectList.front();
	_mObjectList.pop_front();

	return object;
}

template <typename _Ty>
void CObjectFactoryLazy<_Ty>::ReturnFactoryObject(shared_ptr<_Ty> object)
{
	_mObjectList.push_back(object);
}

template <typename _Ty>
uint32 CObjectFactoryLazy<_Ty>::GetMaxObjectCnt() const
{ 
	return _mMaxObjectCnt; 
}

/// <summary>
/// CObjectFactory class with singleton
/// </summary>
template <typename _Ty, size_t size = 10>
class CObjectFactorySgt : public CSingletonPtr<CObjectFactorySgt<_Ty, size>>
{
public:
	CObjectFactorySgt();
	~CObjectFactorySgt() noexcept = default;

	shared_ptr<_Ty> GetFactoryObject();
	void			ReturnFactoryObject(shared_ptr<_Ty> object);

private:
	list<shared_ptr<_Ty>>	_mObjectList;
};

template <typename _Ty, size_t size>
CObjectFactorySgt<_Ty, size>::CObjectFactorySgt()
{
	for (size_t idx = 0; idx < size; ++idx)
	{
		_mObjectList.push_back(make_shared<_Ty>());
	}
}

template <typename _Ty, size_t size>
shared_ptr<_Ty> CObjectFactorySgt<_Ty, size>::GetFactoryObject()
{
	if (_mObjectList.empty())
	{
		throw runtime_error("Error");
	}

	auto object = _mObjectList.front();
	_mObjectList.pop_front();

	return object;
}

template <typename _Ty, size_t size>
void CObjectFactorySgt<_Ty, size>::ReturnFactoryObject(shared_ptr<_Ty> object)
{
	_mObjectList.push_back(object);
}