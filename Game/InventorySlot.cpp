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
	highlight_->AddComponent(ShapeRenderer(Shape::kSquare, 0, 0, 0.3f, 0.5f, false));
	highlight_->GetTransform().SetSize(25, 25);
	highlight_->SetVisible(false);

	auto interactable = AddComponent(Interactable());
	interactable->bounds_ = {0,0, 25, 25};
	interactable->OnHoverEnter += [this] {HandleHoverEnter();};
	interactable->OnHoverExit += [this] {HandleHoverExit(); };
}

void InventorySlot::SetItem(const std::shared_ptr<InventoryItem>& item)
{
	item_ = item;
}

std::shared_ptr<InventoryItem> InventorySlot::Take()
{
	auto item = item_;
	item_ = nullptr;
	return item;
}

void InventorySlot::HandleHoverEnter() const
{
	highlight_->SetVisible(true);
}

void InventorySlot::HandleHoverExit() const
{
	highlight_->SetVisible(false);
}
