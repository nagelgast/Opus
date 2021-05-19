#pragma once

#include "Item.h"
#include "../Opus/Core.h"

class Interactable;

class InventoryItem :
    public Component
{
public:
	explicit InventoryItem(std::shared_ptr<Item> item);
	void Start() override;
	std::shared_ptr<Item> item_;
private:
	void PickUp();
};
