#pragma once
#include "Stat.h"

struct WeaponStats : Stat
{
	WeaponStats(const int min_dmg, const int max_dmg, const int crit_chance, const int aps)
		: min_dmg(min_dmg),
		  max_dmg(max_dmg),
		  crit_chance(crit_chance),
		  aps(aps)
	{
	}

	std::string ToString() override
	{
		std::string text {};
		text += "Physical Damage: " + std::to_string(min_dmg) + "-" + std::to_string(max_dmg) + "\n";
		
		text += "Critical Strike Chance: ";
		char crit_text[4];
		snprintf(crit_text, 4, "%.2g", crit_chance / 100.0);
		text += crit_text;
		text += "%\n";
		
		text += "Attacks per Second: ";
		// TODO My god string manipulation is terrible in C++
		char aps_text[4];
		snprintf(aps_text, 4, "%.2g", aps / 100.0);
		text += aps_text;

		return text;
	}
	
	int min_dmg;
	int max_dmg;
	int crit_chance;
	int aps;
};
