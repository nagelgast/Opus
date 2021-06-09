#include "PlayerInventory.h"

#include <iostream>

#include "Interactable.h"
#include "InventoryItem.h"
#include "InventorySlot.h"
#include "Item.h"

void PlayerInventory::Initialize(MouseSlot& mouse, PlayerInventoryScreen& screen)
{
	mouse_slot_ = &mouse;
	screen_ = &screen;
}

void PlayerInventory::PickUpItem(std::unique_ptr<Item> item) const
{
	if (screen_->IsOpen())
	{
		mouse_slot_->SetItem(std::move(item));
	}
	else
	{
		//if(can_go_to_empty_gear_slot) Equip()

		const auto success = inventory_->TryAutoAddItem(std::move(item));
		if (!success)
		{
			std::cout << "Too. Much. Clutter.\n";
		}
	}
}

std::unique_ptr<Item> PlayerInventory::Equip(InventorySlot& equipment_slot, std::unique_ptr<Item> item)
{
	const auto slot_tag = equipment_slot.GetRequiredTag();
	
	// TODO Check if item can be equipped by player
	if(!item->HasTag(slot_tag)) return item;

	// TODO Allow (equipment) slots to empty themselves
	equipment_slot.GetItem().Remove();
	
	// auto picked_up_item = std::move(equipment_[slot_tag]);
	// equipment_[slot_tag] = std::move(item);
	//
	// screen_->SpawnEquippedItem(equipment_slot, *equipment_[slot_tag]);
	auto picked_up_item = std::move(helmet_);
	helmet_ = std::move(item);
	
	screen_->SpawnEquippedItem(equipment_slot, *helmet_);
	
	return picked_up_item;
}
