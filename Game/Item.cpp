#include "Item.h"

void Item::SetName(std::string name)
{
	name_ = name;
}

Sprite Item::GetSprite() const
{
	return sprite_;
}

void Item::SetSprite(const Sprite& sprite)
{
	sprite_ = sprite;
}
