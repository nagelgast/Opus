#include "pch.h"
#include "CircleCollider.h"

#include "Transform.h"
#include "Vector2.h"

bool CircleCollider::Contains(const Vector2& position)
{
	return Vector2::IsInRange(position, entity_->GetTransform().GetPosition(), radius_);
}

Shape CircleCollider::GetShape()
{
	return Shape::kCircle;
}
