#include "InventorySlot.h"

#include "Interactable.h"
#include "InventoryItem.h"
#include "../Opus/ShapeRenderer.h"
#include "../Opus/SpriteRenderer.h"

void InventorySlot::Awake()
{
	auto& transform = GetTransform();
	const Sprite sprite {"Sprites/InvSlot.png", {0,0, 40, 40}};
	auto sprite_renderer = AddComponent(SpriteRenderer());
	sprite_renderer->SetSprite(sprite, false);

	highlight_ = Instantiate(&transform);
	shape_renderer_ = highlight_->AddComponent(ShapeRenderer(Shape::kSquare, {0, 0, 0, 0.5f}, false));
	highlight_->SetVisible(false);

	auto interactable = AddComponent(Interactable());
}

void InventorySlot::SetItem(std::shared_ptr<InventoryItem> item)
{
	item_ = item;
}

std::shared_ptr<InventoryItem> InventorySlot::GetItem()
{
	return item_;
}

void InventorySlot::ClearItem()
{
	item_ = nullptr;
}

bool InventorySlot::HasItem() const
{
	return item_ != nullptr;
}

void InventorySlot::SetRequiredTag(const ItemTag tag)
{
	required_tag_ = tag;
}

ItemTag InventorySlot::GetRequiredTag() const
{
	return required_tag_;
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
