#pragma once

#include <Windows.h>
#include "Types.h"
#include "Noncopyable.h"

#define dfDEFAULT_STREAMING_BUFFER_SIZE 2

template <size_t SIZE = dfDEFAULT_STREAMING_BUFFER_SIZE>
class CStreamingBuffer : public CNoncopyable
{
public:
	CStreamingBuffer()	= default;
	~CStreamingBuffer() = default;

	void Clear();

	bool IsEmpty()		const;
	bool IsFull()		const;
	int32 GetUsable()	const;
	int32 GetUsed()		const;

	template <typename _Ty>
	bool Push(__in const _Ty* src, __in uint32 size);

	template <typename _Ty>
	CStreamingBuffer& operator << (__in const _Ty* src)
	{
		Push(src, sizeof(_Ty));
		return *this;
	}

	template <typename _Ty>
	bool Pop(__out _Ty* dest, __in uint32 size);

	template <typename _Ty>
	CStreamingBuffer& operator >> (__out _Ty* dest) 
	{ 
		Pop(dest, sizeof(_Ty)); 
		return *this;
	}

private:
	uint32	_mHead		= 0;
	uint32	_mRear		= 0;
	uint32	_mUsed		= 0;

	byte	_mBuf[SIZE] = { 0, };
};

template<size_t SIZE>
inline void CStreamingBuffer<SIZE>::Clear()
{
	::ZeroMemory(_mBuf, sizeof(_mBuf));
}

template<size_t SIZE>
inline bool CStreamingBuffer<SIZE>::IsEmpty() const
{
	return _mHead == _mRear;
}

template<size_t SIZE>
inline bool CStreamingBuffer<SIZE>::IsFull() const
{
	if (_mHead > _mRear)
		return (_mRear + 1) % SIZE == _mHead;

	if (_mHead < _mRear)
		return (_mHead + 1) % SIZE == _mRear;

	return false;
}

template<size_t SIZE>
inline int32 CStreamingBuffer<SIZE>::GetUsable() const
{
	return (SIZE - 1) - _mUsed;
}

template<size_t SIZE>
inline int32 CStreamingBuffer<SIZE>::GetUsed() const
{
	return _mUsed;
}

template<size_t SIZE>
template<typename _Ty>
inline bool CStreamingBuffer<SIZE>::Push(const _Ty* src, uint32 size)
{
	if (nullptr == src)
		return false;

	if (IsFull() || GetUsable() < size)
		return false;

	::memcpy(&_mBuf[_mHead], reinterpret_cast<const byte*>(src), size);
	_mHead = (_mHead + size) % SIZE;
	_mUsed += size;

	return true;
}

template<size_t SIZE>
template<typename _Ty>
inline bool CStreamingBuffer<SIZE>::Pop(_Ty* dest, uint32 size)
{
	if (nullptr == dest)
		return false;

	if (IsEmpty() || _mUsed < size)
		return false;

	::memcpy(reinterpret_cast<byte*>(dest), &_mBuf[_mRear], size);
	_mRear = (_mRear + size) % SIZE;
	_mUsed -= size;

	return false;
}