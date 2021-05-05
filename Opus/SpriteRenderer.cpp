#include "pch.h"
#include "SpriteRenderer.h"

#include "BaseEntityRenderer.h"
#include "Entity.h"

SpriteRenderer::SpriteRenderer(Sprite sprite) : sprite_(sprite)
{
}

void SpriteRenderer::Start()
{
	auto renderer = entity_->CreateRenderer();
	renderer->SetSprite(sprite_);
}
