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
	return Physics::HandleCircleRectCollision(other, *this);
}

void RectCollider::SetOffset(const Vector2 offset)
{
	offset_ = offset;
}

void RectCollider::SetSize(Vector2 size)
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
	auto& transform = entity_->GetTransform();

	const auto pos = transform.GetPosition();
	const auto origin = transform.GetOrigin();
	const auto scale = transform.GetScale();

	const Rect bounds
	{
		pos.y - origin.y + offset_.y,
		pos.x - origin.x + offset_.x,
		scale.x * size_.x,
		scale.y * size_.y
	};

	return bounds;
}
