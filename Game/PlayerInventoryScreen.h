#pragma once

#include "Item.h"
#include "..\Opus\Entity.h"
class InventoryScreen;
class MouseSlot;
class PlayerItemStorage;
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

	InventoryScreen& GetInventoryScreen() const;
private:
	void SpawnEquipmentSlot(ItemTag tag, Vector2 position, float width, float height);

	bool is_open_ = false;
	InventoryScreen* inventory_ = nullptr;

	PlayerItemStorage* player_inventory_ = nullptr;
};
