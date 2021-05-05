#include "pch.h"
#include "SpriteRenderer.h"

#include "BaseEntityRenderer.h"
#include "Entity.h"

void SpriteRenderer::Start()
{
	renderer_ = entity_->CreateRenderer();
	renderer_->SetSprite(sprite_);
}

void SpriteRenderer::SetSprite(const Sprite& sprite)
{
	sprite_ = sprite;
	if(renderer_)
	{
		renderer_->SetSprite(sprite);
	}
}
