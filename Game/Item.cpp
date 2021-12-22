#include "Item.h"

#include <utility>


#include "ItemTag.h"
#include "../Opus/VectorExtensions.h"

const int kInventorySlotSize = 78;

Item::Item(const ItemBaseType& base_type, ItemCategory category, const Rarity rarity, const Rect& texture_rect) :
	base_type_(base_type),
	category_(std::move(category)),
	rarity_(rarity),
	sprite_(Sprite{"Sprites/items.png", texture_rect})
{
}

std::string Item::GetName() const
{
	return base_type_.name;
}

Rarity Item::GetRarity() const
{
	return rarity_;
}

Sprite Item::GetSprite() const
{
	return sprite_;
}

ItemSize Item::GetSize() const
{
	return {category_.width, category_.height};
}

std::string Item::GenerateText() const
{
	std::string text {};
	text += base_type_.category + "\n";
	text += base_type_.stats.GenerateText();
	return text;
}

bool Item::HasTag(const ItemTag& tag)
{
	return Contains(category_.tags, tag);
}
