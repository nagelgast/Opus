#pragma once

class Entity;
class Vector2;
struct Collision;

class Physics
{
public:
	static Collision HandleCollision(const Entity& e, int layer);
	static Collision HandleCollision(const Entity& entity, Entity& other);
	static bool CheckCircleCollision(const Entity& e1, const Entity& e2);
	static bool CheckSquareCollision(const Entity& e1, const Entity& e2);
	static Collision HandleCircleSquareCollision(const Entity& circle, Entity& square);
	static Vector2 ResolveCircleCollision(const Entity& e1, const Entity& e2);
	static Vector2 ResolveSquareCollision(const Entity& e1, const Entity& e2);
};
