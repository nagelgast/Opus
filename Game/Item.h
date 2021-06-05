#pragma once

#include "ItemBaseType.h"
#include "ItemSize.h"
#include "../Opus/Sprite.h"

enum class Rarity;

class Item
{
public:
	explicit Item(ItemBaseType base_type, ItemCategory category, Rarity rarity);
	
	std::string GetName() const;
	Rarity GetRarity() const;
	Sprite GetSprite() const;
	ItemSize GetSize() const;
	bool HasTag(const std::string& required_tag);
private:
	ItemBaseType base_type_;
	ItemCategory category_;
	Rarity rarity_;

	Sprite sprite_;
};
