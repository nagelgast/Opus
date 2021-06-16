#pragma once
#include "Collider.h"
#include "Vector2.h"

class CircleCollider final :
	public Collider
{
public:
	CircleCollider(const int layer, const bool trigger, const bool fixed) : Collider(layer, trigger, fixed)
	{
	}

	Collision HandleCollision(const Collider& other) const override;
	Collision HandleCollision(const RectCollider& other) const override;
	Collision HandleCollision(const CircleCollider& other) const override;

	bool Contains(const Vector2& position) const override;
	Shape GetShape() const override;

private:
	Vector2 offset_{0, 0};
	float radius_ = 1;
};
