#pragma once

#include "ItemBaseType.h"
#include "ItemSize.h"
#include "../Opus/Sprite.h"

enum class ItemTag;
enum class Rarity;

class Item
{
public:
	explicit Item(const ItemBaseType& base_type, ItemCategory category, Rarity rarity, const Rect& texture_rect);
	
	std::string GetName() const;
	Rarity GetRarity() const;
	Sprite GetSprite() const;
	ItemSize GetSize() const;
	std::string GenerateText() const;
	bool HasTag(const ItemTag& tag);
private:
	const ItemBaseType& base_type_;
	ItemCategory category_;
	Rarity rarity_;

	Sprite sprite_;
};
