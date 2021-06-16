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

	void SetRadius(float radius);
	bool Contains(const Vector2& position) const override;
	Shape GetShape() const override;

	float GetGlobalRadius() const;

private:
	float radius_ = 0.5f;
};
