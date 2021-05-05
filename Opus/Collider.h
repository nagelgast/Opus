#pragma once

#include "Component.h"
#include "Shape.h"

class Collider : public Component
{
public:
	explicit Collider(int layer, Shape shape, bool trigger, bool fixed);
	void Collide(const Collider& other) const;

	int GetLayer() const;
	Shape GetShape() const;
	bool IsTrigger() const;
	bool IsFixed() const;
private:
	int layer_;
	Shape shape_;
	bool trigger_;
	bool fixed_;
};
