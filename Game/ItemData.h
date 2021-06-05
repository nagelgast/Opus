#pragma once
#include <map>


#include "ItemBaseType.h"
#include "ItemCategory.h"

class ItemData
{
public:
	ItemData()
	{
		const ItemCategory wands{ "Wands", 1, 3, {"wand", "ranged", "one_hand_weapon", "weapon"} };
		categories_[wands.name] = wands;

		const ItemBaseType driftwood_wand{ "Driftwood_Wand", "Wands", 5, 9, 70, 84 };
		base_types_[driftwood_wand.name] = driftwood_wand;
	}

	ItemBaseType GetBaseType(const std::string& base_type_name)
	{
		return base_types_[base_type_name];
	}

	ItemCategory GetCategory(const std::string& category_name)
	{
		return categories_[category_name];
	}

private:
	std::map<std::string, ItemCategory> categories_;
	std::map<std::string, ItemBaseType> base_types_;
};
