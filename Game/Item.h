#pragma once

#include <vector>

#include "ItemSize.h"
#include "../Opus/Sprite.h"

enum class ItemTag;
//enum class ItemClass;
enum class Rarity;

struct Item
{
//	ItemClass item_class;
	Rarity rarity;
	std::string name;
	Sprite sprite;
	ItemSize size;
	std::vector<ItemTag> tags;
};
