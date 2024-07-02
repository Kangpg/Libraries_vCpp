#pragma once

#include <memory>
#include <unordered_set>
#include <iostream>
#include <cstddef>
#include "Singleton.h"
#include "Types.h"

template <typename _Ty, size_t size = 10>
class CObjectFactory : public CSingletonPtr<CObjectFactory<_Ty, size>>
{
	class CNode : public std::enable_shared_from_this<CNode>
	{
	public:
		CNode(CObjectFactory* pObjectFactory)
			: _mObjectFactory(pObjectFactory), _mObject(std::shared_ptr<_Ty>(new _Ty(), [this](auto p) {ReturnNode(p); })) {}
		~CNode() = default;

		std::shared_ptr<_Ty> GetObject() const
		{
			return _mObject;
		}

		static void ReturnNode(_Ty* object)
		{
			auto node = reinterpret_cast<CNode*>(object);
			node->_mObjectFactory->ReturnObject(node->shared_from_this());
		}

	private:
		std::shared_ptr<_Ty>	_mObject;
		CObjectFactory* _mObjectFactory;
	};

public:
	CObjectFactory()
	{
		for (size_t idx = 0; idx < size; ++idx)
		{
			auto node = std::make_shared<CNode>(this);
			_mObjectList.insert(node);
		}
	}
	~CObjectFactory() = default;

	std::shared_ptr<_Ty> GetObject()
	{
		if (_mObjectList.empty())
		{
			throw std::runtime_error("Error");
		}

		auto itr = _mObjectList.begin();
		auto node = *itr;
		_mObjectList.erase(itr);

		return node->GetObject();
	}

	void ReturnObject(std::shared_ptr<CNode> node)
	{
		_mObjectList.insert(node->shared_from_this());
	}

private:
	std::unordered_set<std::shared_ptr<CNode>>	_mObjectList;
};
