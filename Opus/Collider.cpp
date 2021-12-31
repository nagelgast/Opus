#include "pch.h"
#include "Collider.h"

#include "Entity.h"
#include "Game.h"
#include "Transform.h"

Collider::Collider(const int layer, const bool trigger, const bool fixed)
	: layer_(layer),
	  trigger_(trigger),
	  fixed_(fixed)
{
}

void Collider::Start()
{
	Game::GetCollisionSystem().AddCollider(this);
}

void Collider::OnDestroy()
{
	Game::GetCollisionSystem().RemoveCollider(this);
}

void Collider::Collide(const Collider& other) const
{
	entity_->OnCollision(other);
}

Vector2 Collider::GetGlobalPosition() const
{
	auto& transform = entity_->GetTransform();

	const auto pos = transform.GetPosition();

	return {
		pos.x + offset_.x,
		pos.y + offset_.y
	};
}

void Collider::SetOffset(const Vector2& offset)
{
	offset_ = offset;
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
