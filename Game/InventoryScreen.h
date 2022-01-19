#pragma once

#include "Item.h"
#include "../Opus/Color.h"
#include "../Opus/Core.h"

class PlayerItemStorage;
struct ItemSize;
class Inventory;
class ItemInfoPopup;
class MouseSlot;
class ScreenItem;

class InventorySlot;

class InventoryScreen : public Component
{
public:
	void Initialize(Inventory* inventory, int rows, int columns);
	void SpawnItem(Item& item, const std::vector<int>& slot_indices);
	void RemoveItem(int slot_index);

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

	ScreenItem* pickup_item_ = nullptr;

	PlayerItemStorage* player_inventory_ = nullptr;
};

