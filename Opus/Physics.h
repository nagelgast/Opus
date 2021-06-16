#pragma once
#include "Collider.h"

class Transform;
class Entity;
struct Vector2;
struct Collision;

class Physics
{
public:
	static Collider* GetColliderAtPosition(const Vector2& position, int layer);
	static Collision HandleCollision(Collider& c, int layer);
	static Collision HandleCollision(Collider& c1, Collider& c2);
	
	static bool CheckCircleCollision(const CircleCollider& c1, const CircleCollider& c2);
	static bool CheckRectCollision(const RectCollider& c1, const RectCollider& c2);

	static Vector2 ResolveCircleCollision(const CircleCollider& c1, const CircleCollider& c2);
	static Vector2 ResolveRectCollision(const RectCollider& c1, const RectCollider& c2);

	static Collision HandleCircleRectCollision(const CircleCollider& circle, const RectCollider& rect);
};
