#pragma once
#include "Collider.h"
#include "Rect.h"

class RectCollider final :
	public Collider
{
public:
	RectCollider(const int layer, const bool trigger, const bool fixed) : Collider(layer, trigger, fixed)
	{
	}

	Collision HandleCollision(const Collider& other) const override;
	Collision HandleCollision(const RectCollider& other) const override;
	Collision HandleCollision(const CircleCollider& other) const override;

	void SetOffset(Vector2 offset);
	void SetSize(Vector2 size);
	bool Contains(const Vector2& position) const override;
	Shape GetShape() const override;
	Rect GetGlobalBounds() const;

private:
	Vector2 offset_{0, 0};
	Vector2 size_{1, 1};
};
