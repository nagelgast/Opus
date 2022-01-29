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
	auto& health_bar = CreateChild();
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
	// TODO Make this a separate component
	const auto pos = entity_->GetTransform().GetPosition();
	auto& death_particles = Create(pos);
	const Sprite sprite {"Sprites/particles/circle_05.png"};
	ParticleSettings settings {sprite, {0.3f, 0.3f, 1, 1}, 64, 20, 300};
	settings.lifetime = 0.4f;
	settings.use_scale = true;
	settings.scale_end = 0;
	death_particles.AddComponent(ParticleSystem(settings));

	entity_->Destroy();
}