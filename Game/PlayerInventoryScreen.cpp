#include "PlayerInventoryScreen.h"

#include "EquipmentSlot.h"
#include "Interactable.h"
#include "InventoryScreen.h"
#include "InventorySlot.h"
#include "PlayerItemStorage.h"
#include "../Opus/Shape.h"
#include "../Opus/ShapeRenderer.h"
#include "../Opus/SpriteRenderer.h"
#include "../Opus/Transform.h"

void PlayerInventoryScreen::Awake()
{
	player_inventory_ = Game::GetService<PlayerItemStorage>();

	auto& top_background = SpawnBackground({ 311, 12, 203, 135 }, 2);
	top_background.Move({50, 50});
	auto& bottom_background = SpawnBackground({55, 12, 121, 135}, 2);
	bottom_background.Move({50, 400});
	auto& equipment_background = SpawnBackground({ 191, 32, 109, 113 }, 2);
	equipment_background.Move({ 60, 90 });

	inventory_ = &Instantiate<InventoryScreen>(GetTransform());
	auto& inv_trans = inventory_->GetTransform();
	inv_trans.SetLocalPosition({ 59, 441 });

	SpawnEquipmentSlot(ItemTag::kHelmet, { 145, 100 }, 48, 48);
	SpawnEquipmentSlot(ItemTag::kArmour, { 141, 160 }, 56, 88);
	SpawnEquipmentSlot(ItemTag::kWeapon, { 71, 129 }, 48, 116);
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

InventoryScreen& PlayerInventoryScreen::GetInventoryScreen() const
{
	return *inventory_;
}

void PlayerInventoryScreen::SpawnEquipmentSlot(const ItemTag tag, const Vector2 position, const float width, const float height)
{
	auto& slot = Instantiate<EquipmentSlot>(GetTransform());
	slot.SetName("EquipmentSlot");
	slot.SetRequiredTag(tag);

	auto& slot_transform = slot.GetTransform();
	slot_transform.SetScale(width, height);
	slot_transform.SetLocalPosition(position);
}

Transform& PlayerInventoryScreen::SpawnBackground(const Rect& texture_rect, const float& scale)
{
	auto& background = Instantiate(GetTransform());
	//background.AddComponent(ShapeRenderer(Shape::kSquare, {0.8f, 0.8f, 0.8f}, false));
	auto& sr = background.AddComponent(SpriteRenderer());
	const auto sprite = Sprite{ "Sprites/inventory.png", texture_rect};
	sr.SetSprite(sprite, false);
	auto& transform = background.GetTransform();
	transform.SetScale(texture_rect.width * scale, texture_rect.height * scale);

	return transform;
}
