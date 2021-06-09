#pragma once

#include "ItemBaseType.h"
#include "ItemSize.h"
#include "../Opus/Sprite.h"

enum class ItemTag;
enum class Rarity;

class Item
{
public:
	explicit Item(ItemBaseType base_type, ItemCategory category, Rarity rarity);
	
	std::string GetName() const;
	Rarity GetRarity() const;
	Sprite GetSprite() const;
	ItemSize GetSize() const;
	ItemBaseType GetBaseType() const;
	bool HasTag(const ItemTag& tag);
private:
	ItemBaseType base_type_;
	ItemCategory category_;
	Rarity rarity_;

	Sprite sprite_;
};
