#include "ShapeRenderer.h"

#include "BaseEntityRenderer.h"
#include "Entity.h"

ShapeRenderer::ShapeRenderer(const Shape shape, float r, float g, float b, float a) : shape_(shape), r_(r), g_(g), b_(b), a_(a)
{
}

void ShapeRenderer::Start()
{
	auto renderer = entity_->CreateRenderer();
	renderer->SetShape(shape_, r_, g_, b_, a_);
}

