#pragma once
#include "ItemCategory.h"

struct ItemBaseType
{
	std::string name;
	std::string category;

	int min_dmg = 0;
	int max_dmg = 0;
	int crit_chance = 0;
	int apm = 0;
};
