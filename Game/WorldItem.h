#pragma once

#include "InventoryItem.h"
#include "Item.h"
#include "../Opus/Core.h"

class Targetable;

class WorldItem :
    public Component
{
public:
	explicit WorldItem(const Item& item);
	void Start() override;
	void PickUp();
	std::shared_ptr<Item> item_;
private:
	std::shared_ptr<Targetable> targetable_;
};
