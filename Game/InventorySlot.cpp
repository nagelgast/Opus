#include "InventorySlot.h"

#include "../Opus/SpriteRenderer.h"

void InventorySlot::Awake()
{
	auto& transform = GetTransform();
	const Sprite sprite {"Sprites/InvSlot.png", {0,0, 40, 40}};
	auto sprite_renderer = AddComponent(SpriteRenderer());
	sprite_renderer->SetSprite(sprite, false);
}
