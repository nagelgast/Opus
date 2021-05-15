#pragma once

#include "../Opus/Core.h"

#include "Inventory.h"
#include "MouseItem.h"
#include "PlayerInventoryScreen.h"

class PlayerInventory : public Component
{
public:
	void PickUpItem(std::shared_ptr<Item> item);
	std::shared_ptr<PlayerInventoryScreen> screen_;
	std::shared_ptr<Inventory> inventory_;
	std::shared_ptr<MouseItem> mouse_item_;
private:
	// std::shared_ptr<EquipmentInventory>
};
