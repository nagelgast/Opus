#pragma once

#include "../Opus/Core.h"

#include "Inventory.h"
#include "MouseItem.h"
#include "PlayerInventoryScreen.h"

class PlayerInventory : public Entity
{
public:
	static PlayerInventory& GetInstance();
	void Initialize(const std::shared_ptr<MouseItem>& mouse, const std::shared_ptr<PlayerInventoryScreen>& screen);
	void PickUpItem(const std::shared_ptr<Item>& item) const;
	std::shared_ptr<PlayerInventoryScreen> screen_;
	std::shared_ptr<Inventory> inventory_;
	std::shared_ptr<MouseItem> mouse_item_;
private:
	// std::shared_ptr<EquipmentInventory>

	// TODO Replace with system/service
	static PlayerInventory* instance_;
};
