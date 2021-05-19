#pragma once

#include "../Opus/Core.h"

class Item;
class Interactable;

class InventoryItem :
    public Component
{
public:
	explicit InventoryItem(std::shared_ptr<Item> item);
	std::shared_ptr<Item> item_;
};
