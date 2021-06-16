#include "pch.h"
#include "RectCollider.h"

#include "Vector2.h"

RectCollider::RectCollider(const Rect bounds, const int layer, const bool trigger, const bool fixed)
	: Collider(layer, trigger, fixed),
	  bounds_(bounds)
{
}

bool RectCollider::Contains(const Vector2& position)
{
	return bounds_.Contains(position);
}

Shape RectCollider::GetShape()
{
	return Shape::kSquare;
}

Rect RectCollider::GetGlobalBounds()
{
	return bounds_.ConvertToGlobalSpace(entity_->GetTransform());
}
