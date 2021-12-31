#include "pch.h"
#include "RectCollider.h"

#include "Physics.h"
#include "Transform.h"
#include "Vector2.h"

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
	auto collision = Physics::HandleCircleRectCollision(other, *this);
	// Compensate for swapping the collider order
	collision.displacement.x *= -1;
	collision.displacement.y *= -1;
	return collision;
}

void RectCollider::SetSize(const Vector2 size)
{
	size_ = size;
}

bool RectCollider::Contains(const Vector2& position) const
{
	return GetGlobalBounds().Contains(position);
}

Shape RectCollider::GetShape() const
{
	return Shape::kSquare;
}

Rect RectCollider::GetGlobalBounds() const
{
	const auto& transform = entity_->GetTransform();
	return transform.GetBounds(GetOffset(), size_);
}
