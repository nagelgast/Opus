#include "SpriteRenderer.h"

#include "BaseEntityRenderer.h"
#include "Entity.h"

SpriteRenderer::SpriteRenderer(std::string path, int left, int top, int width, int height) : path_(path), left_(left), top_(top), width_(width), height_(height)
{
}

void SpriteRenderer::Start()
{
	auto renderer = entity_->CreateRenderer();
	renderer->SetSprite(path_, left_, top_, width_, height_);
}
