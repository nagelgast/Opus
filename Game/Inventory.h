#pragma once

#include "../Opus/Color.h"
#include "../Opus/Core.h"

struct ItemSize;
class InventorySlot;
class MouseItem;
class InventoryItem;
class Item;

// TODO Move to global settings
const int kInventorySlotSize = 25;
const Color kItemSlotColor = {0, 0, 0.5, 0.5};
const Color kAvailableSlotColor = { 0, 0.5, 0, 0.5 };
const Color kPickupSlotColor = { 0.5, 0.5, 0, 0.5 };
const Color kUnavailableSlotColor = { 0.5, 0, 0, 0.5 };

class Inventory : public Entity
{
public:
	void Initialize(const std::shared_ptr<MouseItem>& mouse_item);
	void Awake() override;
	bool TryAutoAddItem(const std::shared_ptr<Item>& item);
private:
	void HandleRelease(int index);
	std::shared_ptr<Item> PickupItem();
	void AddItem(const std::shared_ptr<Item>& item, std::vector<int> slot_indices);
	std::vector<int> FindAvailableSlots(const std::shared_ptr<Item>& item);

	std::vector<int> CalculateSlotsToOccupy(ItemSize item_size, int index) const;

	void SetHighlights();
	void ResetHighlights();
	
	void HandleSlotHoverEnter(int index);
	void HandleSlotHoverExit(int index);

	int rows_ = 5;
	int columns_ = 12;

	std::shared_ptr<MouseItem> mouse_item_;
	
	std::vector<std::shared_ptr<InventorySlot>> slots_;
	
	std::vector<int> place_slot_indices_;
	std::vector<int> pickup_slot_indices_;
	std::shared_ptr<InventorySlot> pickup_slot_;
	bool hovering_over_multiple_items_ = false;
};
