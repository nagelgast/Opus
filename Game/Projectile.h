#pragma once

#include "Component.h"
#include "Vector2.h"

class Projectile final : public Component
{
public:
	Projectile(int damage, const Vector2& direction, float speed, float max_distance);
	void Update() override;

private:
	Vector2 direction_;
	int damage_;
	float speed_;
	float max_distance_;
	float distance_traveled_ = 0.f;
};

