#pragma once
#include <utility>

#include "ItemCategory.h"
#include "StatList.h"

struct ItemBaseType
{
	ItemBaseType() = default;
	ItemBaseType(std::string name, std::string category, StatList stats)
		: name(std::move(name)),
		  category(std::move(category)),
		  stats(std::move(stats))
	{
	}

	std::string name;
	std::string category;
	StatList stats;
};
