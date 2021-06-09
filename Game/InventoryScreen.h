#pragma once

#include "Item.h"
#include "../Opus/Color.h"
#include "../Opus/Core.h"

class PlayerInventory;
struct ItemSize;
class Inventory;
class ItemInfoPopup;
class MouseSlot;
class InventoryItem;

class InventorySlot;

class InventoryScreen : public Entity
{
public:
	void Initialize(Inventory* inventory, int rows, int columns);
	void SpawnItem(Item& item, const std::vector<int>& slot_indices);

	// TODO Make private (inventory depends on it)
	std::vector<int> CalculateSlotsToOccupy(ItemSize item_size, int index) const;

private:
	void HandleRelease(int index);
	void HandleSlotHoverEnter(int index);
	void HandleSlotHoverExit(int index);

	void SetHighlights();
	void ResetHighlights();

	Inventory* inventory_ = nullptr;
	int rows_ = 0;
	int columns_ = 0;
	
	std::vector<InventorySlot*> slots_;
	std::vector<int> hover_slot_indices_;
	bool hovering_over_multiple_items_ = false;

	// TODO Should be controlled by mouse handler
	ItemInfoPopup* popup_ = nullptr;

	InventoryItem* pickup_item_ = nullptr;

	PlayerInventory* player_inventory_ = nullptr;
};

