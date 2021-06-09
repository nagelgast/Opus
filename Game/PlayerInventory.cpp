#include "PlayerInventory.h"

#include <iostream>

#include "Interactable.h"
#include "InventoryItem.h"
#include "InventorySlot.h"
#include "Item.h"

void PlayerInventory::Initialize(MouseSlot& mouse, PlayerInventoryScreen& screen)
{
	inventory_ = std::make_unique<Inventory>(screen.GetInventoryScreen(), 5, 12);
	screen_ = &screen;
	mouse_slot_ = &mouse;
}

bool PlayerInventory::IsHoldingItem() const
{
	return mouse_slot_->HasItem();
}

ItemSize PlayerInventory::GetHeldItemSize() const
{
	return mouse_slot_->GetItem().GetSize();
}

void PlayerInventory::HandleEquipmentRelease(InventorySlot& slot)
{
	auto old_mouse_item = mouse_slot_->Take();
	auto new_mouse_item = Equip(slot, std::move(old_mouse_item));
	PickUpItem(std::move(new_mouse_item));

}

void PlayerInventory::ReleasedOverInventorySlot(const int index, const std::vector<int>& hovered_slot_indices)
{
	auto picked_up_item = inventory_->Take(index);

	if (IsHoldingItem())
	{
		const auto success = inventory_->TryPlace(mouse_slot_->Take(), hovered_slot_indices);
		if (!success)
		{
			std::cout << "Error: Couldn't place mouse item!";
		}
	}

	if (picked_up_item)
	{
		PickUpItem(std::move(picked_up_item));
	}
}

void PlayerInventory::PickUpItem(std::unique_ptr<Item> item)
{
	if(!item) return;
	
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

	equipment_slot.RemoveItem();
	
	// auto picked_up_item = std::move(equipment_[slot_tag]);
	// equipment_[slot_tag] = std::move(item);
	//
	// screen_->SpawnEquippedItem(equipment_slot, *equipment_[slot_tag]);
	auto picked_up_item = std::move(helmet_);
	helmet_ = std::move(item);
	
	screen_->SpawnEquippedItem(equipment_slot, *helmet_);
	
	return picked_up_item;
}

bool PlayerInventory::CanEquipHeldItem(const InventorySlot& slot) const
{
	return slot.CanHold(mouse_slot_->GetItem());
}
