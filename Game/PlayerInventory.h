#pragma once

#include "../Opus/Core.h"

#include "Inventory.h"
#include "MouseSlot.h"
#include "PlayerInventoryScreen.h"

class PlayerInventory : public Entity
{
public:
	static PlayerInventory& GetInstance();
	void Initialize(MouseSlot& mouse, PlayerInventoryScreen& screen);
	void PickUpItem(std::unique_ptr<Item> item);
private:
	void SpawnEquipmentSlot(std::string tag, Vector2 position, float width, float height);
	
	void HandleEquipmentSlotHoverEnter(const InventorySlot& slot) const;
	void HandleEquipmentSlotHoverExit(const InventorySlot& slot) const;
	void HandleEquipmentSlotRelease(InventorySlot& slot);

	void Equip(InventorySlot& equipment_slot, std::unique_ptr<Item> item);
		
	PlayerInventoryScreen* screen_ = nullptr;
	Inventory* inventory_ = nullptr;
	MouseSlot* mouse_slot_ = nullptr;
	// std::shared_ptr<EquipmentInventory>

	// TODO Replace with system/service
	static PlayerInventory* instance_;
};
