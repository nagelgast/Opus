#pragma once

#include "../Opus/Core.h"

class InventorySlot;
class MouseItem;
class InventoryItem;
class Item;

class Inventory : public Entity
{
public:
	void Initialize(const std::shared_ptr<MouseItem>& mouse_item);
	void Awake() override;
	void AddItem(const std::shared_ptr<Item>& item);
	void AddItem(const std::shared_ptr<Item>& item, const std::shared_ptr<InventorySlot>& slot) const;
	void HandleRelease(int index);

private:
	std::shared_ptr<InventoryItem> SpawnInventoryItem(const std::shared_ptr<Item>& item) const;

	std::vector<int> CalculateHighlightedSlots(Item& item, int index) const;

	void SetHighlights(const std::vector<int>& slot_indices);
	void ClearHighlights();
	
	void HandleSlotHoverEnter(int index);
	void HandleSlotHoverExit(int index);

	int rows_ = 5;
	int columns_ = 12;

	std::shared_ptr<MouseItem> mouse_item_;
	
	std::vector<std::shared_ptr<InventorySlot>> slots_;
	std::vector<int> highlighted_slots_;
};
