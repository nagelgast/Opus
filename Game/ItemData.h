#pragma once
#include <map>

#include "ImplicitStat.h"
#include "ItemBaseType.h"
#include "ItemCategory.h"
#include "RequirementStats.h"
#include "StatList.h"
#include "WeaponStats.h"

class ItemData
{
public:
	ItemData()
	{
		const ItemCategory wands{"Wand", 1, 3, {ItemTag::kWeapon}};
		categories_["Wands"] = wands;

		StatList stats{};
		// stats.Add(WeaponStats{5, 9, 70, 1400});
		// stats.Add(RequirementStats{0, 0, 0, 14});
		// stats.Add(ImplicitStat{StatGroup::SpellDamage, 8, 12, true});
		const ItemBaseType driftwood_wand{"Driftwood_Wand", "Wands", stats};
		base_types_[driftwood_wand.name] = driftwood_wand;

		const ItemCategory currency{"Currency", 1, 1, {}};
		categories_["Currency"] = currency;
		const ItemBaseType chaos_orb{"Chaos_Orb", "Currency", {}};
		base_types_[chaos_orb.name] = chaos_orb;
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
