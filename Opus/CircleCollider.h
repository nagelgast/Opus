#pragma once
#include "Collider.h"
#include "Vector2.h"

class CircleCollider final :
    public Collider
{
public:
	Collision HandleCollision(const Collider& other) const override;
	Collision HandleCollision(const RectCollider& other) const override;
	Collision HandleCollision(const CircleCollider& other) const override;
	
	bool Contains(const Vector2& position) const override;
	Shape GetShape() const override;
	
private:
	Vector2 offset_;
	float radius_;
};

