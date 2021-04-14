#pragma once

#include "Component.h"
#include "Health.h"
#include "Vector2.h"

class HealthBar final :
	public Component
{
public:
	explicit HealthBar(const std::shared_ptr<Health>& health, const Vector2 offset);

	void Start() override;
	void Update() override;
private:
	const std::weak_ptr<Health> health_;
	const Vector2 offset_;
	float max_width_ = 0;
};
