#pragma once

class Vector2;
class Entity;

struct Collision
{
	Collision() = default;
	Collision(Entity*, const Vector2*);
	const bool hit = false;
	Entity* const other = nullptr;
	const Vector2* const displacement = nullptr;
};

