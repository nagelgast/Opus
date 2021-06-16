#include "pch.h"
#include "RectCollider.h"


#include "Physics.h"
#include "Vector2.h"

RectCollider::RectCollider(const Rect bounds, const int layer, const bool trigger, const bool fixed)
	: Collider(layer, trigger, fixed),
	  bounds_(bounds)
{
}

Collision RectCollider::HandleCollision(const Collider& other) const
{
	return other.HandleCollision(*this);
}

Collision RectCollider::HandleCollision(const RectCollider& other) const
{
	if(!Physics::CheckRectCollision(*this, other)) return {};

	const auto displacement = Physics::ResolveRectCollision(*this, other);
	Collision collision = { entity_, displacement };

	return collision;
}

Collision RectCollider::HandleCollision(const CircleCollider& other) const
{
	return Physics::HandleCircleRectCollision(other, *this);
}

bool RectCollider::Contains(const Vector2& position) const
{
	return bounds_.Contains(position);
}

Shape RectCollider::GetShape() const
{
	return Shape::kSquare;
}

Rect RectCollider::GetGlobalBounds() const
{
	return bounds_.ConvertToGlobalSpace(entity_->GetTransform());
}
