#include "Inventory.h"


#include "InventorySlot.h"
#include "InventoryScreen.h"
#include "Item.h"

const int kEmptySlot = -1;

Inventory::Inventory(InventoryScreen& screen, const int rows, const int columns)
	: screen_(screen),
	  rows_(rows),
	  columns_(columns)
{
	screen.Initialize(this, rows_, columns_);

	// Initialize slot contents to be empty
	for(auto i = 0; i < rows_ * columns_; ++i)
	{
		slot_contents_[i] = -1;
	}
}

std::unique_ptr<Item> Inventory::Take(const int slot_index)
{
	const auto item_index = slot_contents_[slot_index];
	if (item_index == kEmptySlot) return nullptr;

	auto item_slot_indices = slots_per_item_[item_index];
	for (auto item_slot_index : item_slot_indices)
	{
		slot_contents_[item_slot_index] = kEmptySlot;
	}

	screen_.RemoveItem(slot_index);
	
	// TODO Handle vector changes
	slots_per_item_[item_index] = {};
	return std::move(items_[item_index]);
}

bool Inventory::TryAutoAddItem(std::unique_ptr<Item> item)
{
	const auto slot_indices = FindAvailableSlots(item->GetSize());
	const auto has_space = !slot_indices.empty();
	if (has_space)
	{
		Place(std::move(item), slot_indices);
	}

	return has_space;
}

bool Inventory::TryPlace(std::unique_ptr<Item> item, const std::vector<int>& slot_indices)
{
	// TODO Handle everything
	Place(std::move(item), slot_indices);
	return true;
}


std::vector<int> Inventory::FindAvailableSlots(const ItemSize item_size)
{
	for (auto col = 0; col < columns_; ++col)
	{
		for (auto row = 0; row < rows_; ++row)
		{
			const auto index = col + row * columns_;
			auto slot_indices = screen_.CalculateSlotsToOccupy(item_size, index);
			auto is_available = true;
			for (auto slot_index : slot_indices)
			{
				if (slot_contents_[slot_index] != kEmptySlot)
				{
					is_available = false;
					break;
				}
			}
			if (is_available)
			{
				return slot_indices;
			}
		}
	}

	return {};
}

void Inventory::Place(std::unique_ptr<Item> item, const std::vector<int>& slot_indices)
{
	// TODO Handle items
	items_.push_back(std::move(item));
	slots_per_item_.push_back(slot_indices);

	for (auto slot_index : slot_indices)
	{
		slot_contents_[slot_index] = items_.size()-1;
	}
	
	screen_.SpawnItem(*items_.back(), slot_indices);
}
