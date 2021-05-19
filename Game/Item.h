#pragma once

#include "../Opus/Sprite.h"

enum class Rarity;

struct Item
{
	std::string name;
	Sprite sprite;

	int width = 1;
	int height = 1;
};
