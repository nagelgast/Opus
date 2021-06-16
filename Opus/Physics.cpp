#include "pch.h"
#include "Physics.h"

#include "CircleCollider.h"
#include "Collider.h"
#include "Collision.h"
#include "Game.h"
#include "RectCollider.h"
#include "Vector2.h"
#include "Transform.h"

Collider* Physics::GetColliderAtPosition(const Vector2& position, const int layer)
{
	auto colliders = Game::GetCollisionSystem().GetLayerColliders(layer);
	for (const auto& collider : colliders)
	{
		if (collider->Contains(position))
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
	const auto p1 = c1.GetGlobalPosition();
	const auto p2 = c2.GetGlobalPosition();
	const auto r1 = c1.GetGlobalRadius();
	const auto r2 = c2.GetGlobalRadius();

	const auto delta = p1 - p2;
	const auto distance_squared = delta.x * delta.x + delta.y * delta.y;
	const auto radii = r1 + r2;
	const auto radii_squared = radii * radii;

	return distance_squared <= radii_squared;
}

bool Physics::CheckRectCollision(const RectCollider& c1, const RectCollider& c2)
{
	const auto b1 = c1.GetGlobalBounds();
	const auto b2 = c2.GetGlobalBounds();

	if (b1.left > b2.right) return false;
	if (b1.right < b2.left) return false;
	if (b1.top > b2.bottom) return false;
	if (b1.bottom < b2.top) return false;

	return true;
}

Vector2 Physics::ResolveCircleCollision(const CircleCollider& c1, const CircleCollider& c2)
{
	const auto p1 = c1.GetGlobalPosition();
	const auto p2 = c2.GetGlobalPosition();
	const auto r1 = c1.GetGlobalRadius();
	const auto r2 = c2.GetGlobalRadius();

	const auto delta = p1 - p2;
	const auto distance = sqrtf(delta.x * delta.x + delta.y * delta.y);
	const auto overlap = distance - r1 - r2;
	const auto displacement = delta * overlap / distance;

	return Vector2{ displacement };
}

Vector2 Physics::ResolveRectCollision(const RectCollider& c1, const RectCollider& c2)
{
	const auto b1 = c1.GetGlobalBounds();
	const auto b2 = c2.GetGlobalBounds();

	const auto depth_left = b1.right - b2.left;
	const auto depth_right = b1.left - b2.right;
	const auto depth_top = b1.bottom - b2.top;
	const auto depth_bottom = b1.top - b2.bottom;

	const auto depth_hor = abs(depth_left) < abs(depth_right) ? depth_left : depth_right;
	const auto depth_ver = abs(depth_top) < abs(depth_bottom) ? depth_top : depth_bottom;

	if (abs(depth_hor) < abs(depth_ver))
	{
		return { depth_hor, 0 };
	}
	else
	{
		return { 0, depth_ver };
	}
}

Collision Physics::HandleCircleRectCollision(const CircleCollider& circle, const RectCollider& rect)
{
	const auto circle_pos = circle.GetGlobalPosition();
	const auto circle_radius = circle.GetGlobalRadius();

	const auto rect_bounds = rect.GetGlobalBounds();

	const auto closest_x = std::min(rect_bounds.right, std::max(rect_bounds.left, circle_pos.x));
	const auto closest_y = std::min(rect_bounds.bottom, std::max(rect_bounds.top, circle_pos.y));

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
