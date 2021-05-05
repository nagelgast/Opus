#include "Health.h"



#include "HealthBar.h"
#include "../Opus/EntityController.h"
#include "../Opus/ShapeRenderer.h"
#include "../Opus/Shape.h"

Health::Health(int max_health) : current_health_(max_health), max_health_(max_health)
{
}

void Health::Start()
{
	const auto reference = entity_->GetComponent<Health>();
	auto health_bar = entity_->ec_->CreateEntity();
	health_bar->GetTransform().SetSize(50, 10);
	health_bar->AddComponent(HealthBar(reference, {0,-30}));
	health_bar->AddComponent(ShapeRenderer(Shape::kSquare, 1, 0, 0, 0.5f));
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
	entity_->Destroy();
}