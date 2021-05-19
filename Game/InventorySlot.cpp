#include "InventorySlot.h"

#include <iostream>



#include "Interactable.h"
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

void InventorySlot::HandleHoverEnter()
{
	highlight_->SetVisible(true);
	std::cout << "Enter\n";
}

void InventorySlot::HandleHoverExit()
{
	highlight_->SetVisible(false);
	std::cout << "Exit\n";
}
