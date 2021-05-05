#pragma once

#include "Component.h"
#include "Shape.h"

class CollisionSystem;

class Collider : public Component
{
public:
	explicit Collider(int layer, Shape shape, bool trigger, bool fixed);
	~Collider();

	void Start() override;
	
	void Collide(const Collider& other) const;

	int GetLayer() const;
	Shape GetShape() const;
	bool IsTrigger() const;
	bool IsFixed() const;
private:
	CollisionSystem& collision_system_;
	int layer_;
	Shape shape_;
	bool trigger_;
	bool fixed_;
};
