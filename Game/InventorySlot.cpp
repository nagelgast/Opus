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
	shape_renderer_ = highlight_->AddComponent(ShapeRenderer(Shape::kSquare, {0, 0, 0.3f, 0.5f}, false));
	highlight_->GetTransform().SetSize(25, 25);
	highlight_->SetVisible(false);

	auto interactable = AddComponent(Interactable());
	interactable->bounds_ = {0,0, 25, 25};
}

void InventorySlot::SetItem(const std::shared_ptr<InventoryItem>& item)
{
	item_ = item;
}

void InventorySlot::ClearItem()
{
	item_ = nullptr;
}

InventoryItem& InventorySlot::GetItem()
{
	return *item_;
}

bool InventorySlot::HasItem() const
{
	return item_ != nullptr;
}


std::shared_ptr<InventoryItem> InventorySlot::Take()
{
	auto item = item_;
	item_ = nullptr;
	return item;
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
