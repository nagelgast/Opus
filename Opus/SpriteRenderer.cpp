#include "pch.h"
#include "SpriteRenderer.h"

#include "BaseEntityRenderer.h"
#include "Entity.h"
#include "Game.h"

void SpriteRenderer::Awake()
{
	renderer_ = entity_->CreateRenderer();
}

void SpriteRenderer::SetSprite(const Sprite& sprite) const
{
	const auto texture = Game::GetTextureManager().Get(sprite.path);
	renderer_->SetTexture(*texture);
	renderer_->SetTextureRect(sprite.rect);
}

void SpriteRenderer::ResetSprite() const
{
	renderer_->Reset();
}

void SpriteRenderer::SetMirrored(bool value) const
{
	renderer_->SetMirrored(value);
}
