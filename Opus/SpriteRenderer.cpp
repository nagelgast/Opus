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

void SpriteRenderer::Mirror()
{
	// TODO Should not be tracked both here and in the actual renderer
	mirrored_ = !mirrored_;
	renderer_->Mirror();
}

bool SpriteRenderer::IsMirrored() const
{
	return mirrored_;
}