#pragma once
#include "Stat.h"

struct RequirementStats : Stat
{
	RequirementStats(const int level, const int strength, const int dexterity, const int intelligence)
		: level(level),
		  strength(strength),
		  dexterity(dexterity),
		  intelligence(intelligence)
	{
	}

	std::string ToString() override
	{
		std::string text {"Requires "};
		auto has_any_requirement = false;
		
		if (level > 1)
		{
			has_any_requirement = true;
			text += "Level " + std::to_string(level) + ", ";
		}
		if (strength > 1)
		{
			has_any_requirement = true;
			text += std::to_string(strength) + " Str, ";
		}
		if (dexterity > 1)
		{
			has_any_requirement = true;
			text += std::to_string(dexterity) + " Dex, ";
		}
		if (intelligence > 1)
		{
			has_any_requirement = true;
			text += std::to_string(intelligence) + " Int, ";
		}

		// Remove last comma
		text.pop_back();
		text.pop_back();

		return has_any_requirement ? text : "";
	}

	int level;
	int strength;
	int dexterity;
	int intelligence;
};
