#pragma once

#include "Item.h"
#include "../Opus/Core.h"

class InventoryItem :
    public Entity
{
public:
	explicit InventoryItem(std::shared_ptr<const Item> item);
private:
	const std::shared_ptr<const Item> item_;
};
