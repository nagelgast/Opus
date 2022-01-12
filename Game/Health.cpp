#include "Health.h"

#include "HealthBar.h"
#include "../Opus/ShapeRenderer.h"
#include "../Opus/ParticleSystem.h"
#include "../Opus/Shape.h"

Health::Health(int max_health) : current_health_(max_health), max_health_(max_health)
{
}

void Health::Start()
{
	auto& health_bar = entity_->Instantiate(entity_->GetTransform());
	health_bar.SetName("HealthBar");

	auto& transform = health_bar.GetTransform();
	transform.SetScale(50, 10);
	transform.SetLocalPosition({ 0, -30 });
	
	health_bar.AddComponent(HealthBar(*this));
	health_bar.AddComponent(ShapeRenderer(Shape::kSquare, {1, 0, 0, 0.5f}));
}

void Health::TakeDamage(int amount)
{
	current_health_ -= amount;
	if (current_health_ <= 0)
	{
		Die();
	}
}

int Health::GetHealth() const
{
	return current_health_;
}

int Health::GetMaxHealth() const
{
	return max_health_;
}

void Health::Die()
{
	const auto pos = entity_->GetTransform().GetPosition();
	auto& death_particles = entity_->Instantiate(pos);
	const Sprite sprite {"Sprites/particles/circle_05.png"};
	const ParticleSettings settings {sprite, 64};
	death_particles.AddComponent(ParticleSystem(settings));

	entity_->Destroy();
}