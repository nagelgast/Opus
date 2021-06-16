#pragma once
#include "Collider.h"
class CircleCollider final :
    public Collider
{
public:
	bool Contains(const Vector2& position) override;
	Shape GetShape() override;
private:
	float radius_;
};

