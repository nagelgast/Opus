#pragma once

#include "../Opus/Core.h"

#include "Inventory.h"
#include "ItemTag.h"
#include "MouseItem.h"
#include "PlayerInventoryScreen.h"

class PlayerInventory : public Entity
{
public:
	static PlayerInventory& GetInstance();
	void Initialize(const std::shared_ptr<MouseItem>& mouse, const std::shared_ptr<PlayerInventoryScreen>& screen);
	void PickUpItem(const std::shared_ptr<Item>& item) const;
private:
	void SpawnEquipmentSlot(ItemTag tag, Vector2 position, float width, float height);
	void HandleEquipmentSlotHoverEnter(std::shared_ptr<InventorySlot> slot);
	void HandleEquipmentSlotHoverExit(std::shared_ptr<InventorySlot> slot);
	void HandleEquipmentSlotRelease(std::shared_ptr<InventorySlot> slot);

	std::shared_ptr<PlayerInventoryScreen> screen_;
	std::shared_ptr<Inventory> inventory_;
	std::shared_ptr<MouseItem> mouse_item_;
	// std::shared_ptr<EquipmentInventory>

	// TODO Replace with system/service
	static PlayerInventory* instance_;
};
