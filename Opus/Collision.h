#pragma once

class Entity;

#include "Vector2.h"

struct __declspec(dllexport) Collision
{
	Collision() = default;
	Collision(Entity* const e, const Vector2& v) : hit(true), other(e), displacement(v) {}
	const bool hit = false;
	Entity* const other = nullptr;
	Vector2 displacement;
};
