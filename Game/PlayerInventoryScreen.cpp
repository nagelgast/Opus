#include "PlayerInventoryScreen.h"



#include "Interactable.h"
#include "Inventory.h"
#include "InventoryItem.h"
#include "InventoryScreen.h"
#include "InventorySlot.h"
#include "MouseSlot.h"
#include "PlayerInventory.h"
#include "../Opus/Shape.h"
#include "../Opus/ShapeRenderer.h"
#include "../Opus/Transform.h"

void PlayerInventoryScreen::Awake()
{
	player_inventory_ = Game::GetService<PlayerInventory>();
	auto background = &Instantiate(GetTransform());
	background->AddComponent(ShapeRenderer(Shape::kSquare, {0.8f, 0.8f, 0.8f}, false));

	auto& transform = background->GetTransform();
	transform.SetScale(350, 768);

	auto& screen_transform = GetTransform();

	inventory_ = &Instantiate<InventoryScreen>(screen_transform);
	auto& inv_trans = inventory_->GetTransform();
	inv_trans.SetLocalPosition({ 25, 550 });

	SpawnEquipmentSlot("helmet", { 175, 150 }, 50, 50);
	SpawnEquipmentSlot("body", { 175, 275 }, 50, 100);
	SpawnEquipmentSlot("weapon", { 100, 275 }, 50, 100);
}

void PlayerInventoryScreen::Open()
{
	if(is_open_)
	{
		Close();
	}
	else
	{
		is_open_ = true;
		SetVisible(true);
	}
}

void PlayerInventoryScreen::Close()
{
	is_open_ = false;
	SetVisible(false);
}

bool PlayerInventoryScreen::IsOpen() const
{
	return is_open_;
}

void PlayerInventoryScreen::SpawnEquipmentSlot(std::string tag, Vector2 position, float width, float height)
{
	auto& background = Instantiate();
	background.AddComponent(ShapeRenderer(Shape::kSquare, { 0.2f, 0.2f, 0.2f }, false));
	auto& background_transform = background.GetTransform();

	background_transform.SetScale(width, height);

	auto& slot = Instantiate<InventorySlot>(GetTransform());
	slot.SetRequiredTag(tag);

	auto* interactable = slot.GetComponent<Interactable>();
	interactable->OnHoverEnter += [this, &slot] { slot.SetEquippableHighlight(); };
	interactable->OnHoverExit += [this, &slot] { slot.DisableHighlight(); };
	interactable->OnRelease += [this, &slot] { player_inventory_->HandleEquipmentRelease(slot); };

	auto& slot_transform = slot.GetTransform();
	slot_transform.SetScale(width, height);
	slot_transform.SetLocalPosition(position);

	// TODO Implement sorting so we don't have to rely on instantiation order
	background_transform.SetParent(slot_transform);
	background_transform.SetLocalPosition({ 0, 0 });
}

void PlayerInventoryScreen::SpawnEquippedItem(InventorySlot& slot, Item& item)
{
	// TODO Should be part of equipment slot itself
	auto slot_transform = slot.GetTransform();
	auto& inventory_item = Instantiate<InventoryItem>(slot_transform);
	inventory_item.Initialize(item, { &slot });
}

InventoryScreen& PlayerInventoryScreen::GetInventoryScreen()
{
	return *inventory_;
}
