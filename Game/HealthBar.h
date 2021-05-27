#pragma once

#include "../Opus/Core.h"

class Health;

class HealthBar final :
	public Component
{
public:
	explicit HealthBar(const Health& health);

	void Start() override;
	void Update() override;
private:
	const Health* health_;
	float max_width_ = 0;
	float height_ = 0;
};
