#include "pch.h"
#include "CircleCollider.h"


#include "Physics.h"
#include "Transform.h"
#include "Vector2.h"

Collision CircleCollider::HandleCollision(const Collider& other) const
{
	return other.HandleCollision(*this);
}

Collision CircleCollider::HandleCollision(const RectCollider& other) const
{
	return Physics::HandleCircleRectCollision(*this, other);
}

Collision CircleCollider::HandleCollision(const CircleCollider& other) const
{
	if (!Physics::CheckCircleCollision(*this, other)) return {};

	const auto displacement = Physics::ResolveCircleCollision(*this, other);
	Collision collision = {entity_, displacement};
	
	return collision;
}

bool CircleCollider::Contains(const Vector2& position) const
{
	return Vector2::IsInRange(position, entity_->GetTransform().GetPosition(), radius_);
}

Shape CircleCollider::GetShape() const
{
	return Shape::kCircle;
}