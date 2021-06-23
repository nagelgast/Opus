#pragma once
#include "Stat.h"
#include "StatGroup.h"

struct ImplicitStat : Stat
{
	ImplicitStat(const StatGroup group, const int min, const int max, const bool global)
		: group(group),
		  min(min),
		  max(max),
		  global(global)
	{
	}

	std::string ToString() override
	{
		// TODO Make generic
		return "(" + std::to_string(min) + "-" + std::to_string(max) + ")% increased Spell Damage";
	}
	
	StatGroup group;
	int min;
	int max;
	bool global;
};
