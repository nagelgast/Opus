#include "Item.h"

#include <utility>

#include "../Opus/VectorExtensions.h"

const int kInventorySlotSize = 78;

Item::Item(ItemBaseType base_type, ItemCategory category, const Rarity rarity) :
	base_type_(std::move(base_type)),
	category_(std::move(category)),
	rarity_(rarity),
	sprite_(Sprite{
		"Sprites/" + base_type_.name + "_inventory_icon.png",
		{0, 0, category_.width * kInventorySlotSize, category_.height * kInventorySlotSize}
	})
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

bool Item::HasTag(const std::string& required_tag)
{
	return Contains(category_.tags, required_tag);
}
