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

void PlayerInventory::Initialize(const std::shared_ptr<MouseSlot>& mouse,
                                 const std::shared_ptr<PlayerInventoryScreen>& screen)
{
	instance_ = this;

	mouse_slot_ = mouse;
	screen_ = screen;

	const auto screen_transform = &screen_->GetTransform();

	inventory_ = Instantiate<Inventory>(screen_transform);
	auto& inv_trans = inventory_->GetTransform();
	inv_trans.SetLocalPosition({25, 550});

	inventory_->Initialize(mouse_slot_);

	SpawnEquipmentSlot(ItemTag::helmet, {175, 150}, 50, 50);
	SpawnEquipmentSlot(ItemTag::body, {175, 275}, 50, 100);
	SpawnEquipmentSlot(ItemTag::weapon, {100, 275}, 50, 100);
}

void PlayerInventory::PickUpItem(const std::shared_ptr<Item>& item) const
{
	if (screen_->IsOpen())
	{
		mouse_slot_->SetItem(item);
	}
	else
	{
		//if(can_go_to_empty_gear_slot) Equip()

		const auto success = inventory_->TryAutoAddItem(item);
		if (!success)
		{
			std::cout << "Too. Much. Clutter.\n";
		}
	}
}

void PlayerInventory::SpawnEquipmentSlot(ItemTag tag, Vector2 position, float width, float height)
{
	auto background = Instantiate();
	background->AddComponent(ShapeRenderer(Shape::kSquare, {0.2f, 0.2f, 0.2f}, false));
	auto& background_transform = background->GetTransform();

	background_transform.SetScale(width, height);

	auto slot = Instantiate<InventorySlot>(&screen_->GetTransform());
	slot->SetRequiredTag(tag);

	auto interactable = slot->GetComponent<Interactable>();
	interactable->OnHoverEnter += [this, slot] { HandleEquipmentSlotHoverEnter(slot); };
	interactable->OnHoverExit += [this, slot] { HandleEquipmentSlotHoverExit(slot); };
	interactable->OnRelease += [this, slot] { HandleEquipmentSlotRelease(slot); };

	auto& slot_transform = slot->GetTransform();
	slot_transform.SetScale(width, height);
	slot_transform.SetLocalPosition(position);

	// TODO Implement sorting so we don't have to rely on instantiation order
	background_transform.SetParent(&slot_transform);
	background_transform.SetLocalPosition({0, 0});
}

void PlayerInventory::HandleEquipmentSlotHoverEnter(std::shared_ptr<InventorySlot> slot)
{
	if (mouse_slot_->HasItem() && !slot->CanHold(mouse_slot_->GetItem()))
	{
		slot->EnableHighlight(kUnavailableSlotColor);
	}
	else
	{
		slot->EnableHighlight(kAvailableSlotColor);
	}
}

void PlayerInventory::HandleEquipmentSlotHoverExit(std::shared_ptr<InventorySlot> slot)
{
	slot->DisableHighlight();
}

void PlayerInventory::HandleEquipmentSlotRelease(const std::shared_ptr<InventorySlot>& slot)
{
	std::cout << "Released\n";
	if (mouse_slot_->HasItem())
	{
		if (slot->CanHold(mouse_slot_->GetItem()))
		{
			// Store the mouse item
			const auto blub = mouse_slot_->Take();

			// Pick up the equipped item
			// TODO INLINING THIS IS CRASH???
			TryPickup(slot);

			Equip(slot, blub);
		}
	}
	else
	{
		if (slot->HasItem())
		{
			const auto item = slot->GetItem()->Take();
			mouse_slot_->SetItem(item);
		}
	}
}


void PlayerInventory::TryPickup(const std::shared_ptr<InventorySlot>& slot)
{
	if (slot->HasItem())
	{
		mouse_slot_->SetItem(slot->GetItem()->Take());
	}
}

void PlayerInventory::Equip(std::shared_ptr<InventorySlot> equipment_slot, std::shared_ptr<Item> item)
{
	auto slot_transform = equipment_slot->GetTransform();

	const auto inventory_item = Instantiate<InventoryItem>(&slot_transform);
	inventory_item->Initialize(inventory_item, item, {equipment_slot});
}

PlayerInventory* PlayerInventory::instance_;
