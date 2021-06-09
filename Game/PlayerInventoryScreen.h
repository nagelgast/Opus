#pragma once

#include "Item.h"
#include "..\Opus\Entity.h"
class MouseSlot;
class PlayerInventory;
class InventorySlot;
class Inventory;

class PlayerInventoryScreen :
    public Entity
{
public:
	void Awake() override;
	void Open();
	void Close();

	bool IsOpen() const;

	void SpawnEquippedItem(InventorySlot& slot, Item& item);
private:
	void SpawnEquipmentSlot(std::string tag, Vector2 position, float width, float height);

	void HandleEquipmentSlotHoverEnter(const InventorySlot& slot) const;
	void HandleEquipmentSlotHoverExit(const InventorySlot& slot) const;
	void HandleEquipmentSlotRelease(InventorySlot& slot);

	bool is_open_ = false;
	Inventory* inventory_ = nullptr;

	PlayerInventory* player_inventory_ = nullptr;
	MouseSlot* mouse_slot_ = nullptr;
};
