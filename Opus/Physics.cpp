#include "pch.h"
#include "Physics.h"

#include "CircleCollider.h"
#include "Collider.h"
#include "Collision.h"
#include "Entity.h"
#include "Game.h"
#include "RectCollider.h"
#include "Vector2.h"
#include "Transform.h"

Collider* Physics::GetColliderAtPosition(const Vector2& position, const int layer)
{
	auto colliders = Game::GetCollisionSystem().GetLayerColliders(layer);
	for (const auto& collider : colliders)
	{
		if(collider->Contains(position))
		{
			return collider;
		}
	}

	return nullptr;
}

Collision Physics::HandleCollision(Collider& c, const int layer)
{
	auto colliders = Game::GetCollisionSystem().GetLayerColliders(layer);
	for (const auto& collider : colliders)
	{
		const auto collision = HandleCollision(c, *collider);
		if (collision.hit)
		{
			return collision;
		}

	}

	return {};
}

Collision Physics::HandleCollision(Collider& c1, Collider& c2)
{
	return c1.HandleCollision(c2);
}

bool Physics::CheckCircleCollision(const CircleCollider& c1, const CircleCollider& c2)
{
	const auto t1 = c1.entity_->GetTransform();
	const auto t2 = c2.entity_->GetTransform();
	
	const auto pos1 = t1.GetPosition();
	const auto pos2 = t2.GetPosition();

	const auto r1 = t1.GetScale().x / 2.f;
	const auto r2 = t2.GetScale().x / 2.f;

	const auto delta = pos1 - pos2;
	const auto distance_squared = delta.x * delta.x + delta.y * delta.y;
	const auto radii = r1 + r2;
	const auto radii_squared = radii * radii;

	return distance_squared <= radii_squared;
}

bool Physics::CheckRectCollision(const RectCollider& c1, const RectCollider& c2)
{
	const auto c1_bounds = c1.GetGlobalBounds();
	const Vector2 c1_top_left {c1_bounds.left, c1_bounds.top};
	const Vector2 c1_bottom_right {c1_bounds.left + c1_bounds.width, c1_bounds.top + c1_bounds.height};

	const auto c2_bounds = c2.GetGlobalBounds();
	const Vector2 c2_top_left{ c2_bounds.left, c2_bounds.top };
	const Vector2 c2_bottom_right{ c2_bounds.left + c2_bounds.width, c2_bounds.top + c2_bounds.height };

	if (c1_top_left.x > c2_bottom_right.x) return false;
	if (c1_bottom_right.x < c2_top_left.x) return false;
	if (c1_top_left.y > c2_bottom_right.y) return false;
	if (c1_bottom_right.y < c2_top_left.y) return false;

	return true;
}

Vector2 Physics::ResolveCircleCollision(const CircleCollider& c1, const CircleCollider& c2)
{
	const auto t1 = c1.entity_->GetTransform();
	const auto t2 = c2.entity_->GetTransform();
	
	const auto p1 = t1.GetPosition();
	const auto p2 = t2.GetPosition();
	const auto delta = p1 - p2;
	const auto distance = sqrtf(delta.x * delta.x + delta.y * delta.y);
	const auto overlap = distance - t1.GetScale().x / 2.f - t2.GetScale().x / 2.f;
	const auto displacement = delta * overlap / distance;

	return Vector2 {displacement};
}

Vector2 Physics::ResolveRectCollision(const RectCollider& c1, const RectCollider& c2)
{
	const auto b1 = c1.GetGlobalBounds();
	const Vector2 p1 { b1.left, b1.top };
	const Vector2 s1 { b1.width, b1.height };

	const auto b2 = c2.GetGlobalBounds();
	const Vector2 p2 = { b2.left, b2.top };
	const Vector2 s2 = { b2.width, b2.height };

	const auto depth_left = p1.x + s1.x - p2.x;
	const auto depth_right = p1.x - (p2.x + s2.x);
	const auto depth_top = p1.y + s1.y - p2.y;
	const auto depth_bottom = p1.y - (p2.y + s2.y);

	const auto depth_hor = abs(depth_left) < abs(depth_right) ? depth_left : depth_right;
	const auto depth_ver = abs(depth_top) < abs(depth_bottom) ? depth_top : depth_bottom;

	if(abs(depth_hor) < abs(depth_ver))
	{
		return {depth_hor, 0};
	}
	else
	{
		return {0, depth_ver};
	}
}

Collision Physics::HandleCircleRectCollision(const CircleCollider& circle, const RectCollider& rect)
{
	const auto circle_transform = circle.entity_->GetTransform();
	const auto rect_transform = rect.entity_->GetTransform();
	
	const auto circle_pos = circle_transform.GetPosition();
	const auto circle_radius = circle_transform.GetScale().x / 2.f;
	const auto square_center = rect_transform.GetPosition();
	const auto square_size = rect_transform.GetScale();
	const auto square_origin = rect_transform.GetOrigin();
	const auto square_top_left = square_center - square_origin;
	const auto square_bottom_right = square_top_left + square_size;

	const auto closest_x = std::min(square_bottom_right.x, std::max(square_top_left.x, circle_pos.x));
	const auto closest_y = std::min(square_bottom_right.y, std::max(square_top_left.y, circle_pos.y));

	const Vector2 closest_pos = { closest_x, closest_y };

	const auto ray_to_nearest = (closest_pos - circle_pos);
	const auto distance = ray_to_nearest.GetLength();
	if (distance <= circle_radius)
	{
		const auto displacement = ray_to_nearest / distance * (circle_radius - distance);

		auto c = Collision(rect.entity_, displacement);
		return c;
	}

	return {};
}
