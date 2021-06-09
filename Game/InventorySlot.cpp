#include "InventorySlot.h"

#include "Interactable.h"
#include "ScreenItem.h"
#include "Item.h"
#include "PlayerItemStorage.h"
#include "../Opus/ShapeRenderer.h"
#include "../Opus/SpriteRenderer.h"

void InventorySlot::Awake()
{
	storage_ = Game::GetService<PlayerItemStorage>();
	
	auto& transform = GetTransform();
	const Sprite sprite {"Sprites/InvSlot.png", {0,0, 40, 40}};
	const auto sprite_renderer = AddComponent(SpriteRenderer());
	sprite_renderer.SetSprite(sprite, false);

	highlight_ = &Instantiate(transform);
	shape_renderer_ = &highlight_->AddComponent(ShapeRenderer(Shape::kSquare, {0, 0, 0, 0.5f}, false));
	highlight_->SetVisible(false);

	auto interactable = AddComponent(Interactable());

	interactable.OnHoverEnter += [this] { SetEquippableHighlight(); };
	interactable.OnHoverExit += [this] { DisableHighlight(); };
	interactable.OnRelease += [this] { HandleRelease(); };

}

void InventorySlot::SetItem(ScreenItem& item)
{
	item_ = &item;
}

ScreenItem& InventorySlot::GetItem() const
{
	return *item_;
}

void InventorySlot::ClearItem()
{
	item_ = nullptr;
}

void InventorySlot::RemoveItem() const
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
	if(required_tag_ == ItemTag::kNoTag) return true;
	
	return item.HasTag(required_tag_);
}

void InventorySlot::SetRequiredTag(const ItemTag& tag)
{
	required_tag_ = tag;
}

ItemTag InventorySlot::GetRequiredTag() const
{
	return required_tag_;
}

void InventorySlot::HandleRelease()
{
	storage_->HandleEquipmentRelease(*this);
}

void InventorySlot::SetEquippableHighlight() const
{
	if (storage_->IsHoldingItem() && !storage_->CanEquipHeldItem(*this))
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
