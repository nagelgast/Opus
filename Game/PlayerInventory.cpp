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
	slot->SetRequiredTag(ItemTag::weapon);

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
	slot->EnableHighlight(kAvailableSlotColor);
}

void PlayerInventory::HandleEquipmentSlotHoverExit(std::shared_ptr<InventorySlot> slot)
{
	slot->DisableHighlight();
}

void PlayerInventory::HandleEquipmentSlotRelease(std::shared_ptr<InventorySlot> slot)
{
	std::shared_ptr<Item> picked_up_item = nullptr;

	if (slot->HasItem())
	{
		picked_up_item = slot->GetItem().GetItem();
	}

	if (mouse_slot_->HasItem())
	{
		if (Contains(mouse_slot_->GetItem().tags, slot->GetRequiredTag()))
		{
			// Equip the item
			auto item = mouse_slot_->Take();

			// Create new inventory item instance
			const auto inventory_item = Instantiate<InventoryItem>(&GetTransform());
			inventory_item->Initialize(item);

			// Position item correctly
			auto& transform = inventory_item->GetTransform();
			const Vector2 offset = { (item->size.width - 1) / 2, kInventorySlotSize * (item->size.height - 1) / 2 };
			transform.SetPosition(slot->GetTransform().GetPosition());

		}
		else
		{
			return;
		}
	}
	
	if (picked_up_item)
	{
		mouse_slot_->SetItem(picked_up_item);
	}
}

PlayerInventory* PlayerInventory::instance_;
