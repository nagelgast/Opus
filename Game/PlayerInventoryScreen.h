#pragma once

#include "Item.h"
#include "../Opus/Core.h"

class InventoryScreen;
class MouseSlot;
class PlayerItemStorage;
class InventorySlot;
class Inventory;

class PlayerInventoryScreen :
    public Component
{
public:
	void Awake() override;
	void Open();
	void Close();

	bool IsOpen() const;

	InventoryScreen& GetInventoryScreen() const;
private:
	void SpawnEquipmentSlot(ItemTag tag, Vector2 position, float width, float height);
	Transform& SpawnBackground(const Rect& texture_rect, const float& scale);

	bool is_open_ = false;
	InventoryScreen* inventory_ = nullptr;

	PlayerItemStorage* player_inventory_ = nullptr;
};
