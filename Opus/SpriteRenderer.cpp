#include "pch.h"
#include "SpriteRenderer.h"

#include "BaseEntityRenderer.h"
#include "Entity.h"

void SpriteRenderer::Awake()
{
	renderer_ = entity_->CreateRenderer();
}

void SpriteRenderer::SetSprite(const Sprite& sprite, bool world_space) const
{
	renderer_->SetSprite(sprite);
	renderer_->in_world_space_ = world_space;
}

void SpriteRenderer::ResetSprite() const
{
	renderer_->Reset();
}

void SpriteRenderer::SetMirrored(bool value) const
{
	renderer_->SetMirrored(value);
}
