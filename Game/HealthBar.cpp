#include "HealthBar.h"

#include "ShapeRenderer.h"

HealthBar::HealthBar(const std::shared_ptr<Health>& health, const Vector2 offset) : health_(health), offset_(offset)
{
}

void HealthBar::Start()
{
	max_width_ = entity_->GetScale().x;
}

void HealthBar::Update()
{
	if (health_.expired())
	{
		entity_->Destroy();
		return;
	}

	auto health = health_.lock();

	// TODO: Handle event-based?
	auto height = entity_->GetScale().y;
	float health_remaining = (float) health->GetHealth() / health->GetMaxHealth();
	entity_->SetSize(max_width_ * health_remaining, height);
	auto pos = health->entity_->GetPosition() + offset_;
	entity_->SetPosition(health->entity_->GetPosition() + offset_);
}
