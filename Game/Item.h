#pragma once

#include "ItemSize.h"
#include "../Opus/Sprite.h"

enum class Rarity;

struct Item
{
	std::string name;
	Sprite sprite;

	ItemSize size;
};
