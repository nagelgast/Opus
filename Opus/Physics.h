#pragma once

class Transform;
class Entity;
class Vector2;
struct Collision;

class __declspec(dllexport) Physics
{
public:
	static Collision HandleCollision(Entity& e, int layer);
	static Collision HandleCollision(Entity& entity, Entity& other);
	static bool CheckCircleCollision(const Transform& t1, const Transform& t2);
	static bool CheckSquareCollision(const Transform& t1, const Transform& t2);
	static Collision HandleCircleSquareCollision(const Transform& circle, Transform& square);
	static Vector2 ResolveCircleCollision(const Transform& t1, const Transform& t2);
	static Vector2 ResolveSquareCollision(const Transform& t1, const Transform& t2);
};
