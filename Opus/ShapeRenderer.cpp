#include "pch.h"
#include "ShapeRenderer.h"

#include "BaseEntityRenderer.h"
#include "Entity.h"

ShapeRenderer::ShapeRenderer(const Shape shape, const Color color, const bool in_world_space) :
	shape_(shape),
	color_(color),
	in_world_space_(in_world_space)
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
	renderer_->in_world_space_ = in_world_space_;
	renderer_->SetShape(shape_);
	renderer_->SetColor(color_);
}
