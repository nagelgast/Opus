#pragma once
#include "Collider.h"
#include "Rect.h"

class RectCollider :
    public Collider
{
public:
	explicit RectCollider(Rect bounds, int layer, bool trigger, bool fixed);
	
	Collision HandleCollision(const Collider& other) const override;
	Collision HandleCollision(const RectCollider& other) const override;
	Collision HandleCollision(const CircleCollider& other) const override;

	bool Contains(const Vector2& position) const override;
	Shape GetShape() const override;
	Rect GetGlobalBounds() const;
	
private:
	Rect bounds_;
};

