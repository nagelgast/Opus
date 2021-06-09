#pragma once
#include <string>
#include <vector>

#include "ItemTag.h"

struct ItemCategory
{
	std::string name;
	int width = 1;
	int height = 1;

	std::vector<ItemTag> tags;
};
