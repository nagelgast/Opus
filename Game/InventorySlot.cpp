#include "InventorySlot.h"

#include "Interactable.h"
#include "InventoryItem.h"
#include "Item.h"
#include "PlayerInventory.h"
#include "../Opus/ShapeRenderer.h"
#include "../Opus/SpriteRenderer.h"

void InventorySlot::Awake()
{
	player_inventory_ = Game::GetService<PlayerInventory>();
	
	auto& transform = GetTransform();
	const Sprite sprite {"Sprites/InvSlot.png", {0,0, 40, 40}};
	auto sprite_renderer = AddComponent(SpriteRenderer());
	sprite_renderer.SetSprite(sprite, false);

	highlight_ = &Instantiate(transform);
	shape_renderer_ = &highlight_->AddComponent(ShapeRenderer(Shape::kSquare, {0, 0, 0, 0.5f}, false));
	highlight_->SetVisible(false);

	auto interactable = AddComponent(Interactable());
}

void InventorySlot::SetItem(InventoryItem& item)
{
	item_ = &item;
}

InventoryItem& InventorySlot::GetItem() const
{
	return *item_;
}

void InventorySlot::ClearItem()
{
	item_ = nullptr;
}

void InventorySlot::RemoveItem()
{
	if(item_)
	{
		item_->Remove();
	}
}

bool InventorySlot::HasItem() const
{
	return item_ != nullptr;
}

bool InventorySlot::CanHold(Item& item) const
{
	if(required_tag_ == "no_tag") return true;
	
	return item.HasTag(required_tag_);
}

void InventorySlot::SetRequiredTag(const std::string& tag)
{
	required_tag_ = tag;
}

std::string InventorySlot::GetRequiredTag() const
{
	return required_tag_;
}

void InventorySlot::SetEquippableHighlight() const
{
	if (player_inventory_->IsHoldingItem() && !player_inventory_->CanEquipHeldItem(*this))
	{
		EnableHighlight(kUnavailableSlotColor);
	}
	else
	{
		EnableHighlight(kAvailableSlotColor);
	}
}

void InventorySlot::EnableHighlight(const Color color) const
{
	highlight_->SetVisible(true);
	shape_renderer_->SetColor(color);
}

void InventorySlot::DisableHighlight() const
{
	highlight_->SetVisible(false);
}
