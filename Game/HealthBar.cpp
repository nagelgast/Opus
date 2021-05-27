#include "HealthBar.h"


#include "Health.h"
#include "../Opus/ShapeRenderer.h"

HealthBar::HealthBar(const Health& health) : health_(&health)
{
}

void HealthBar::Start()
{
	max_width_ = entity_->GetTransform().GetScale().x;
	height_ = entity_->GetTransform().GetScale().y;
}

void HealthBar::Update()
{
	if (!health_)
	{
		return;
	}

	// TODO: Handle event-based?
	auto health_remaining = static_cast<float>(health_->GetHealth()) / static_cast<float>(health_->GetMaxHealth());
	health_remaining += 0.5f;
	entity_->GetTransform().SetScale(max_width_ * health_remaining, height_);
}
