#pragma once

#include "Item.h"
#include "../Opus/Core.h"

class InventoryItem :
    public Component
{
public:
	explicit InventoryItem(std::shared_ptr<Item> item);
	std::shared_ptr<Item> item_;
};

