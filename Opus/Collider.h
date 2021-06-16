#pragma once

#include "Component.h"
#include "Shape.h"

class CollisionSystem;

class Collider : public Component
{
public:
	void Start() override;
	void OnDestroy() override;
	
	void Collide(const Collider& other) const;

	int GetLayer() const;
	bool IsTrigger() const;
	bool IsFixed() const;
	virtual Shape GetShape() = 0;
	virtual bool Contains(const Vector2& position) = 0;
protected:
	explicit Collider(int layer, bool trigger, bool fixed);
private:
	int layer_;
	bool trigger_;
	bool fixed_;
};
