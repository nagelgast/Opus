#include "PlayerInventory.h"

#include <iostream>



#include "Interactable.h"
#include "InventorySlot.h"
#include "Item.h"
#include "../Opus/ShapeRenderer.h"

PlayerInventory& PlayerInventory::GetInstance()
{
	return *instance_;
}

void PlayerInventory::Initialize(const std::shared_ptr<MouseItem>& mouse,
                                 const std::shared_ptr<PlayerInventoryScreen>& screen)
{
	instance_ = this;

	mouse_item_ = mouse;
	screen_ = screen;

	const auto screen_transform = &screen_->GetTransform();

	inventory_ = Instantiate<Inventory>(screen_transform);
	auto& inv_trans = inventory_->GetTransform();
	inv_trans.SetLocalPosition({0, 250});

	inventory_->Initialize(mouse_item_);

	SpawnEquipmentSlot(ItemTag::helmet, {0, -250}, 50, 50);
	SpawnEquipmentSlot(ItemTag::body, {0, -200}, 50, 100);
	SpawnEquipmentSlot(ItemTag::weapon, {-50, -200}, 50, 100);
}

void PlayerInventory::PickUpItem(const std::shared_ptr<Item>& item) const
{
	if (screen_->IsOpen())
	{
		mouse_item_->TryAddItem(item);
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

	background_transform.SetSize(width, height);

	auto slot = Instantiate<InventorySlot>(&screen_->GetTransform());
	slot->SetRequiredTag(ItemTag::weapon);

	auto interactable = slot->GetComponent<Interactable>();
	interactable->OnHoverEnter += [this, slot] {HandleEquipmentSlotHoverEnter(slot);};
	interactable->OnHoverExit += [this, slot] {HandleEquipmentSlotHoverExit(slot); };
	interactable->OnRelease += [this, slot] {HandleEquipmentSlotRelease(slot); };

	auto& slot_transform = slot->GetTransform();
	slot_transform.SetSize(width, height);
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
	
}

PlayerInventory* PlayerInventory::instance_;
