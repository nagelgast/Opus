#include "pch.h"
#include "Collider.h"


#include "Entity.h"
#include "Game.h"


Collider::Collider(const int layer, const Shape shape, const bool trigger, const bool fixed)
	: collision_system_(Game::GetCollisionSystem()),
	  layer_(layer),
	  shape_(shape),
	  trigger_(trigger),
	  fixed_(fixed)
{
}

Collider::~Collider()
{
	collision_system_.RemoveCollider(this);
}

void Collider::Start()
{
	collision_system_.AddCollider(this);
}

void Collider::Collide(const Collider& other) const
{
	entity_->OnCollision(other);
}

bool Collider::IsTrigger() const
{
	return trigger_;
}

bool Collider::IsFixed() const
{
	return fixed_;
}

int Collider::GetLayer() const
{
	return layer_;
}

Shape Collider::GetShape() const
{
	return shape_;
}
