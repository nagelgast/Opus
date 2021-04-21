#pragma once

#include "Component.h"
#include "Shape.h"

class OPUS_API Collider : public Component
{
public:
	explicit Collider(int layer, Shape shape);

	int layer_ = 0;
	Shape shape_ = Shape::kCircle;
};
