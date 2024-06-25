#pragma once

template <typename _Ty>
class CSingletonRef
{
protected:
	CSingleton() = default;
	~CSingleton() = default;

public:
	static _Ty& GetInstance() const
	{
		static _Ty _mInstance;
		return _mInstance;
	}
};

// swap �� ������ �����͸� ����� �̱��� ��ü�� �ʿ�?