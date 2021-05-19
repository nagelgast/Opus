#include "pch.h"
#include "SpriteRenderer.h"

#include "BaseEntityRenderer.h"
#include "Entity.h"

// TODO Improve this logic
void SpriteRenderer::Start()
{
	renderer_ = entity_->CreateRenderer();
	renderer_->SetSprite(sprite_);
	renderer_->in_world_space_ = world_space_;
}

void SpriteRenderer::SetSprite(const Sprite& sprite, bool world_space)
{
	sprite_ = sprite;
	if(renderer_)
	{
		renderer_->SetSprite(sprite);
		renderer_->in_world_space_ = world_space;
	}
	else
	{
		world_space_ = world_space;
	}
}

void SpriteRenderer::ResetSprite()
{
	sprite_ = {};
	if(renderer_)
	{
		renderer_->Reset();
	}
}
