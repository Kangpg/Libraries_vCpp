#pragma once

#include "pch.h"
#include "Singleton.h"

template <typename _Ty, size_t size = 10>
class CObjectFactory : public CSingletonPtr<CObjectFactory<_Ty, size>>
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
