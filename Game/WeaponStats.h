#pragma once
#include "Stat.h"

struct WeaponStats : Stat
{
	WeaponStats(const int min_dmg, const int max_dmg, const int crit_chance, const int apm)
		: min_dmg(min_dmg),
		  max_dmg(max_dmg),
		  crit_chance(crit_chance),
		  apms(apm)
	{
	}

	std::string ToString() override
	{
		std::string text {};
		text += "Physical Damage: " + std::to_string(min_dmg) + "-" + std::to_string(max_dmg) + "\n";
		text += "Critical Strike Chance: " + std::to_string(crit_chance / 100.0) + "%\n";
		text += "Attacks per Second: ";

		// TODO My god string manipulation is terrible in C++
		char aps[4];
		snprintf(aps, 4, "%.2f", apms / 1000.0);
		text += aps;

		return text;
	}
	
	int min_dmg;
	int max_dmg;
	int crit_chance;
	int apms;
};
