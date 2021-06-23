#pragma once
#include <string>

struct Stat
{
	virtual ~Stat() = default;
	
	virtual std::string ToString() = 0;
};
