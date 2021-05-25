#pragma once

#include <vector>

#include "ItemSize.h"
#include "../Opus/Sprite.h"

enum class ItemTag;
enum class Rarity;

struct Item
{
	std::string name;
	Sprite sprite;
	ItemSize size;
	std::vector<ItemTag> tags;
};
