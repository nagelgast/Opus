#pragma once

#include "Component.h"
#include "Shape.h"

class OPUS_API Collider : public Component
{
public:
	explicit Collider(int layer, Shape shape, bool fixed);
	void Collide(const Collider& other) const;

	int layer_;
	Shape shape_;
	bool fixed_;
};
