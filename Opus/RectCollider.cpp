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
	// TODO Cache this
	const auto& transform = entity_->GetTransform();
	const auto scale = transform.GetScale();
	const auto width = scale.x * size_.x;
	const auto height = scale.y * size_.y;


	const auto global_pos = GetGlobalPosition();
	const Rect bounds
	{
		global_pos.x - width * 0.5f,
		global_pos.y - height * 0.5f,
		width,
		height
	};

	return bounds;
}
