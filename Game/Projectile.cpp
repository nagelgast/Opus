#include "Projectile.h"

#include "Health.h"

#include "../Opus/Collision.h"
#include "../Opus/Physics.h"

Projectile::Projectile(int damage, const float speed, const float max_distance)
:	damage_(damage),
	speed_(speed),
	max_distance_(max_distance),
	hit_(false)
{
}

void Projectile::SetDirection(const Vector2& direction)
{
	direction_ = direction;
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
	if(hit_) return;
	
	hit_ = true;
	auto health = other.entity_->GetComponent<Health>();
	if (health)
	{
		health->TakeDamage(damage_);
	}
	entity_->Destroy();
}