#include "HealthBar.h"

#include "../Opus/ShapeRenderer.h"
#include "../Opus/Transform.h"

HealthBar::HealthBar(const std::shared_ptr<Health>& health, const Vector2 offset) : health_(health), offset_(offset)
{
}

void HealthBar::Start()
{
	max_width_ = entity_->GetTransform().GetScale().x;
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
	auto height = entity_->GetTransform().GetScale().y;
	float health_remaining = (float) health->GetHealth() / health->GetMaxHealth();
	entity_->GetTransform().SetSize(max_width_ * health_remaining, height);
	auto pos = health->entity_->GetTransform().GetPosition() + offset_;
	entity_->GetTransform().SetPosition(health->entity_->GetTransform().GetPosition() + offset_);
}
