#pragma once

class CNoncopyable
{
protected:
	CNoncopyable() = default;
	virtual ~CNoncopyable() = default;

public:
	CNoncopyable(const CNoncopyable&)					= delete;
	CNoncopyable& operator=(const CNoncopyable&)		= delete;
	CNoncopyable(CNoncopyable&&) noexcept				= delete;
	CNoncopyable& operator=(CNoncopyable&&)	 noexcept	= delete;
};