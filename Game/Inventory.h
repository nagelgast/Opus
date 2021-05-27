#pragma once

#include "../Opus/Color.h"
#include "../Opus/Core.h"

struct Item;
struct ItemSize;
class InventorySlot;
class MouseSlot;
class InventoryItem;

// TODO Move to global settings
const int kInventorySlotSize = 25;
const Color kItemSlotColor = {0, 0, 0.5, 0.5};
const Color kAvailableSlotColor = { 0, 0.5, 0, 0.5 };
const Color kPickupSlotColor = { 0.5, 0.5, 0, 0.5 };
const Color kUnavailableSlotColor = { 0.5, 0, 0, 0.5 };

class Inventory : public Entity
{
public:
	void Initialize(MouseSlot& mouse_item);
	void Awake() override;
	bool TryAutoAddItem(std::unique_ptr<Item> item);
private:
	void HandleRelease(int index);
	void Place(std::unique_ptr<Item> item, const std::vector<int>& slot_indices);
	
	std::vector<int> FindAvailableSlots(ItemSize item_size);
	std::vector<int> CalculateSlotsToOccupy(ItemSize item_size, int index) const;

	void SetHighlights();
	void ResetHighlights();
	
	void HandleSlotHoverEnter(int index);
	void HandleSlotHoverExit(int index);

	int rows_ = 5;
	int columns_ = 12;

	MouseSlot* mouse_item_ = nullptr;
	InventoryItem* pickup_item_ = nullptr;

	std::vector<InventorySlot*> slots_;
	std::vector<int> hover_slot_indices_;

	
	bool hovering_over_multiple_items_ = false;
};
