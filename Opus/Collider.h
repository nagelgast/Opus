#pragma once

#include "Collision.h"
#include "Component.h"
#include "Shape.h"

class CollisionSystem;

class Collider : public Component
{
public:
	Collider(int layer, bool trigger, bool fixed);

	void Start() override;
	void OnDestroy() override;

	// TODO Find more elegant way to solve this
	// Done to avoid the need for dynamic_cast
	virtual Collision HandleCollision(const Collider& other) const = 0;
	virtual Collision HandleCollision(const RectCollider& other) const = 0;
	virtual Collision HandleCollision(const CircleCollider& other) const = 0;

	void Collide(const Collider& other) const;

	int GetLayer() const;
	bool IsTrigger() const;
	bool IsFixed() const;
	virtual Shape GetShape() const = 0;
	virtual bool Contains(const Vector2& position) const = 0;
private:
	int layer_;
	bool trigger_;
	bool fixed_;
};
