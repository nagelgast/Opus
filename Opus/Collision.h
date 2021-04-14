#pragma once

class Vector2;
class Entity;

struct __declspec(dllexport) Collision
{
	Collision() = default;
	Collision(Entity* const e, const Vector2* const v) : hit(true), other(e), displacement(v) {}
	const bool hit = false;
	Entity* const other = nullptr;
	const Vector2* const displacement = nullptr;
};

