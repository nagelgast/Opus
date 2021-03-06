#pragma once

#include "../Opus/Color.h"
#include "../Opus/Core.h"

class InventoryScreen;
class ItemInfoPopup;
class Item;
struct ItemSize;
class InventorySlot;
class MouseSlot;
class ScreenItem;


class Inventory
{
public:
	Inventory(InventoryScreen& screen, int rows, int columns);
	std::unique_ptr<Item> Take(int slot_index);
	bool TryAutoAddItem(std::unique_ptr<Item> item);
	bool TryPlace(std::unique_ptr<Item> item, const std::vector<int>& slot_indices);
private:
	void Place(std::unique_ptr<Item> item, const std::vector<int>& slot_indices);
	std::vector<int> FindAvailableSlots(ItemSize item_size);

	InventoryScreen& screen_;
	const int rows_;
	const int columns_;

	// Key -> slot index, Value -> item index
	std::map<int, int> slot_contents_;

	// Serialized data
	std::vector<std::unique_ptr<Item>> items_;
	std::vector<std::vector<int>> slots_per_item_;
};
