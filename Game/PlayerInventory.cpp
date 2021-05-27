#include "PlayerInventory.h"

#include <iostream>


#include "Interactable.h"
#include "InventoryItem.h"
#include "InventorySlot.h"
#include "Item.h"
#include "../Opus/ShapeRenderer.h"

PlayerInventory& PlayerInventory::GetInstance()
{
	return *instance_;
}

void PlayerInventory::Initialize(MouseSlot& mouse, PlayerInventoryScreen& screen)
{
	instance_ = this;

	mouse_slot_ = &mouse;
	screen_ = &screen;

	auto& screen_transform = screen_->GetTransform();

	inventory_ = &Instantiate<Inventory>(screen_transform);
	auto& inv_trans = inventory_->GetTransform();
	inv_trans.SetLocalPosition({25, 550});

	inventory_->Initialize(*mouse_slot_);

	SpawnEquipmentSlot(ItemTag::helmet, {175, 150}, 50, 50);
	SpawnEquipmentSlot(ItemTag::body, {175, 275}, 50, 100);
	SpawnEquipmentSlot(ItemTag::weapon, {100, 275}, 50, 100);
}

void PlayerInventory::PickUpItem(std::unique_ptr<Item> item)
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

void PlayerInventory::SpawnEquipmentSlot(ItemTag tag, Vector2 position, float width, float height)
{
	auto& background = Instantiate();
	background.AddComponent(ShapeRenderer(Shape::kSquare, {0.2f, 0.2f, 0.2f}, false));
	auto& background_transform = background.GetTransform();

	background_transform.SetScale(width, height);

	auto& slot = Instantiate<InventorySlot>(screen_->GetTransform());
	slot.SetRequiredTag(tag);

	auto* interactable = slot.GetComponent<Interactable>();
	interactable->OnHoverEnter += [this, &slot] { HandleEquipmentSlotHoverEnter(slot); };
	interactable->OnHoverExit += [this, &slot] { HandleEquipmentSlotHoverExit(slot); };
	interactable->OnRelease += [this, &slot] { HandleEquipmentSlotRelease(slot); };

	auto& slot_transform = slot.GetTransform();
	slot_transform.SetScale(width, height);
	slot_transform.SetLocalPosition(position);

	// TODO Implement sorting so we don't have to rely on instantiation order
	background_transform.SetParent(slot_transform);
	background_transform.SetLocalPosition({0, 0});
}

void PlayerInventory::HandleEquipmentSlotHoverEnter(const InventorySlot& slot) const
{
	if (mouse_slot_->HasItem() && !slot.CanHold(mouse_slot_->GetItem()))
	{
		slot.EnableHighlight(kUnavailableSlotColor);
	}
	else
	{
		slot.EnableHighlight(kAvailableSlotColor);
	}
}

void PlayerInventory::HandleEquipmentSlotHoverExit(const InventorySlot& slot) const
{
	slot.DisableHighlight();
}

void PlayerInventory::HandleEquipmentSlotRelease(InventorySlot& slot)
{
	if (mouse_slot_->HasItem())
	{
		if (slot.CanHold(mouse_slot_->GetItem()))
		{
			// Store the mouse item
			auto mouse_item = mouse_slot_->Take();

			// Pick up the equipped item
			if (slot.HasItem())
			{
				PickUpItem(slot.GetItem().TakeItem());
			}

			Equip(slot, std::move(mouse_item));
		}
	}
	else
	{
		if (slot.HasItem())
		{
			PickUpItem(slot.GetItem().TakeItem());
		}
	}
}

void PlayerInventory::Equip(InventorySlot& equipment_slot, std::unique_ptr<Item> item)
{
	auto slot_transform = equipment_slot.GetTransform();

	auto& inventory_item = Instantiate<InventoryItem>(slot_transform);
	inventory_item.Initialize(std::move(item), {&equipment_slot});
}

PlayerInventory* PlayerInventory::instance_;
