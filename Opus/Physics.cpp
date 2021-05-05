#include "pch.h"
#include "Physics.h"

#include "Collider.h"
#include "Collision.h"
#include "Entity.h"
#include "Shape.h"
#include "Vector2.h"
#include "Transform.h"

Collision Physics::HandleCollision(Collider& c, const int layer)
{
	auto& entities = c.entity_->GetEntities();

	for (const auto& entity : entities)
	{
		//TODO Fix really slow
		auto col = entity->GetComponent<Collider>();
		if (col != nullptr && col->GetLayer() == layer)
		{
			const auto collision = HandleCollision(c, *col);
			if(collision.hit)
			{
				return collision;
			}
		}
	}

	return {};
}

Collision Physics::HandleCollision(Collider& player, Collider& other)
{
	const auto is_circle1 = player.GetShape() == Shape::kCircle;
	const auto is_circle2 = other.GetShape() == Shape::kCircle;

	const auto& t1 = player.entity_->GetTransform();
	auto& t2 = other.entity_->GetTransform();
	if(is_circle1 && is_circle2)
	{
		const auto collision = CheckCircleCollision(t1, t2);
		if(collision)
		{
			const auto displacement = ResolveCircleCollision(t1, t2);
			return Collision{other.entity_, displacement};
		}
	}
	if(!is_circle1 && !is_circle2)
	{
		const auto collision = CheckSquareCollision(t1, t2);
		if(collision)
		{
			const auto displacement = ResolveSquareCollision(t1, t2);
			return Collision{other.entity_, displacement};
		}
	}
	if(is_circle1 && !is_circle2)
	{
		return HandleCircleSquareCollision(t1, t2);
	}
	if (!is_circle1 && is_circle2)
	{
		// TODO: Implement circle/square collisions
	}

	return {};
}

bool Physics::CheckCircleCollision(const Transform& t1, const Transform& t2)
{
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

bool Physics::CheckSquareCollision(const Transform& t1, const Transform& t2)
{
	const auto p1 = t1.GetPosition() - t1.GetOrigin();
	const auto s1 = t1.GetScale();

	const auto p2 = t2.GetPosition() - t2.GetOrigin();
	const auto s2 = t2.GetScale();

	if (p1.x > p2.x + s2.x) return false;
	if (p1.x + s1.x < p2.x) return false;
	if (p1.y > p2.y + s2.y) return false;
	if (p1.y + s1.y < p2.y) return false;

	return true;
}

Collision Physics::HandleCircleSquareCollision(const Transform& circle, Transform& square)
{
	const auto circle_pos = circle.GetPosition();
	const auto circle_radius = circle.GetScale().x/2.f;
	const auto square_center = square.GetPosition();
	const auto square_size = square.GetScale();
	const auto square_origin = square.GetOrigin();
	const auto square_top_left = square_center - square_origin;
	const auto square_bottom_right = square_top_left + square_size;

	const auto closest_x = std::min(square_bottom_right.x, std::max(square_top_left.x, circle_pos.x));
	const auto closest_y = std::min(square_bottom_right.y, std::max(square_top_left.y, circle_pos.y));

	const Vector2 closest_pos = {closest_x, closest_y};
	
	const auto ray_to_nearest = (closest_pos - circle_pos);
	const auto distance = ray_to_nearest.GetLength();
	if(distance <= circle_radius)
	{
		const auto displacement = ray_to_nearest/distance * (circle_radius - distance);
		
		auto c = Collision(square.entity_, displacement);
		return c;
	}

	return {};
}

Vector2 Physics::ResolveCircleCollision(const Transform& t1, const Transform& t2)
{
	const auto p1 = t1.GetPosition();
	const auto p2 = t2.GetPosition();
	const auto delta = p1 - p2;
	const auto distance = sqrtf(delta.x * delta.x + delta.y * delta.y);
	const auto overlap = distance - t1.GetScale().x / 2.f - t2.GetScale().x / 2.f;
	const auto displacement = delta * overlap / distance;

	return Vector2 {displacement};
}

Vector2 Physics::ResolveSquareCollision(const Transform& t1, const Transform& t2)
{
	const auto p1 = t1.GetPosition() - t1.GetOrigin();
	const auto s1 = t1.GetScale();

	const auto p2 = t2.GetPosition() - t2.GetOrigin();
	const auto s2 = t2.GetScale();

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