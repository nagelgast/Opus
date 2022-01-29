#include "PlayerInventoryScreen.h"

#include "EquipmentSlot.h"
#include "Interactable.h"
#include "InventoryScreen.h"
#include "InventorySlot.h"
#include "PlayerItemStorage.h"
#include "../Opus/SpriteRenderer.h"
#include "../Opus/Transform.h"

void PlayerInventoryScreen::Awake()
{
	player_inventory_ = Game::GetService<PlayerItemStorage>();

	auto& top_background = SpawnBackground({ 311, 12, 203, 135 }, 2);
	top_background.Move({250, 182});
	auto& bottom_background = SpawnBackground({55, 12, 121, 135}, 2);
	bottom_background.Move({170, 530});
	auto& equipment_background = SpawnBackground({ 191, 32, 109, 113 }, 2);
	equipment_background.Move({ 170, 200 });

	inventory_ = &CreateChild<InventoryScreen>();
	auto& inv_trans = inventory_->GetTransform();
	inv_trans.SetLocalPosition({ 75, 452 });

	SpawnEquipmentSlot(ItemTag::kHelmet, { 170, 120 }, 48, 48);
	SpawnEquipmentSlot(ItemTag::kArmour, { 170, 200 }, 56, 88);
	SpawnEquipmentSlot(ItemTag::kWeapon, { 96, 185 }, 48, 116);
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
		entity_->SetVisible(true);
	}
}

void PlayerInventoryScreen::Close()
{
	is_open_ = false;
	entity_->SetVisible(false);
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
	auto& slot = CreateChild<EquipmentSlot>("EquipmentSlot");
	slot.SetRequiredTag(tag);

	auto& slot_transform = slot.GetTransform();
	slot_transform.SetScale(width, height);
	slot_transform.SetLocalPosition(position);
}

Transform& PlayerInventoryScreen::SpawnBackground(const Rect& texture_rect, const float& scale)
{
	auto& background = CreateChild();
	auto& sr = background.AddComponent(SpriteRenderer());
	const auto sprite = Sprite{ "Sprites/inventory.png", texture_rect};
	sr.SetSprite(sprite);
	auto& transform = background.GetTransform();
	transform.SetScale(scale, scale);

	return transform;
}
