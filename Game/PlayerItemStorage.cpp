#include "PlayerItemStorage.h"

#include <iostream>

#include "EquipmentSlot.h"
#include "Interactable.h"
#include "InventorySlot.h"
#include "Item.h"

void PlayerItemStorage::Initialize(MouseSlot& mouse, PlayerInventoryScreen& screen)
{
	inventory_ = std::make_unique<Inventory>(screen.GetInventoryScreen(), kInventoryRows, kInventoryColumns);
	screen_ = &screen;
	mouse_slot_ = &mouse;
}

bool PlayerItemStorage::IsHoldingItem() const
{
	return mouse_slot_->HasItem();
}

ItemSize PlayerItemStorage::GetHeldItemSize() const
{
	return mouse_slot_->GetItem().GetSize();
}

void PlayerItemStorage::HandleEquipmentRelease(EquipmentSlot& slot)
{
	auto old_mouse_item = mouse_slot_->Take();
	auto new_mouse_item = Equip(slot, std::move(old_mouse_item));
	PickUpItem(std::move(new_mouse_item));
}

void PlayerItemStorage::HandleInventoryRelease(const int index, const std::vector<int>& hovered_slot_indices) const
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

void PlayerItemStorage::PickUpItem(std::unique_ptr<Item> item) const
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

std::unique_ptr<Item> PlayerItemStorage::Equip(EquipmentSlot& equipment_slot, std::unique_ptr<Item> item)
{
	const auto tag = equipment_slot.GetRequiredTag();
	
	// If we can't equip the new item, do nothing
	if(item && !item->HasTag(tag))
	{
		return item;
	}

	// TODO Check properly if item can be equipped by player

	// Get the currently equipped item
	equipment_slot.RemoveItem();
	auto picked_up_item = std::move(equipment_[tag]);

	// Equip the new item, if any
	if(item)
	{
		equipment_[tag] = std::move(item);
		equipment_slot.SpawnItem(*equipment_[tag]);
	}

	// Return the previously equipped item
	return picked_up_item;
}

bool PlayerItemStorage::CanEquipHeldItem(const EquipmentSlot& slot) const
{
	return slot.CanHold(mouse_slot_->GetItem());
}
