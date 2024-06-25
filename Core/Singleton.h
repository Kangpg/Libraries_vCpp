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

// swap 이 가능한 포인터를 사용한 싱글톤 객체도 필요?