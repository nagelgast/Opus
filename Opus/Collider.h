#pragma once

#include "Component.h"
#include "Shape.h"

class Collider : public Component
{
public:
	OPUS_API explicit Collider(int layer, Shape shape, bool trigger, bool fixed);
	OPUS_API void Collide(const Collider& other) const;

	OPUS_API int GetLayer() const;
	OPUS_API Shape GetShape() const;
	OPUS_API bool IsTrigger() const;
	OPUS_API bool IsFixed() const;
private:
	int layer_;
	Shape shape_;
	bool trigger_;
	bool fixed_;
};
