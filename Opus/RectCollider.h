#pragma once
#include "Collider.h"
#include "Rect.h"

class RectCollider :
    public Collider
{
public:
	explicit RectCollider(Rect bounds, int layer, bool trigger, bool fixed);
	
	bool Contains(const Vector2& position) override;
	Shape GetShape() override;
	Rect GetGlobalBounds();
private:
	Rect bounds_;
};

