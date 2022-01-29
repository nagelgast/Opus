#include "pch.h"
#include "ShapeRenderer.h"

#include "BaseEntityRenderer.h"
#include "Entity.h"

ShapeRenderer::ShapeRenderer(const Shape shape, const Color color) :
	shape_(shape),
	color_(color)
{
}

void ShapeRenderer::SetColor(const Color color)
{
	color_ = color;
	renderer_->SetColor(color_);
}

void ShapeRenderer::Awake()
{
	renderer_ = entity_->CreateRenderer();
	renderer_->SetShape(shape_);
	renderer_->SetColor(color_);
}
