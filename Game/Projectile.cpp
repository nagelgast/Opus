#include "Projectile.h"

#include "../Opus/Collision.h"
#include "../Opus/Entity.h"
#include "../Opus/Physics.h"
#include "Health.h"
#include "../Opus/Transform.h"

Projectile::Projectile(int damage, const Vector2& direction, const float speed, const float max_distance)
:	direction_(direction),
	damage_(damage),
	speed_(speed),
	max_distance_(max_distance)
{
}

void Projectile::Update()
{
	const auto dt = entity_->GetDeltaTime();

	auto pos = entity_->GetTransform().GetPosition();
	const auto dx = direction_.x * speed_ * dt;
	const auto dy = direction_.y * speed_ * dt;
	entity_->GetTransform().Move({dx, dy});

	// Check for distance
	distance_traveled_ += abs(dx) + abs(dy);

	if (distance_traveled_ > max_distance_)
	{
		entity_->Destroy();
	}
}

void Projectile::OnCollision(const Collider& other)
{
	auto health = other.entity_->GetComponent<Health>();
	if (health)
	{
		health->TakeDamage(damage_);
	}
	entity_->Destroy();
}