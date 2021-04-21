#pragma once
#include "Collider.h"

class Transform;
class Entity;
class Vector2;
struct Collision;

class Physics
{
public:
	static Collision HandleCollision(Collider& c, int layer);
	static Collision HandleCollision(Collider& player, Collider& other);
	static bool CheckCircleCollision(const Transform& t1, const Transform& t2);
	static bool CheckSquareCollision(const Transform& t1, const Transform& t2);
	static Collision HandleCircleSquareCollision(const Transform& circle, Transform& square);
	static Vector2 ResolveCircleCollision(const Transform& t1, const Transform& t2);
	static Vector2 ResolveSquareCollision(const Transform& t1, const Transform& t2);
};
