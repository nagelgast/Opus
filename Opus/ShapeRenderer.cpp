#include "pch.h"
#include "ShapeRenderer.h"

#include "BaseEntityRenderer.h"
#include "Entity.h"

ShapeRenderer::ShapeRenderer(const Shape shape, float r, float g, float b, float a, bool in_world_space) : shape_(shape), r_(r), g_(g), b_(b), a_(a), in_world_space_(in_world_space)
{
}

void ShapeRenderer::Start()
{
	auto renderer = entity_->CreateRenderer();
	renderer->in_world_space_ = in_world_space_;
	renderer->SetShape(shape_, r_, g_, b_, a_);
}

