#pragma once

#include "../Opus/Collider.h"
#include "../Opus/Component.h"
#include "../Opus/Vector2.h"

class Projectile final : public Component
{
public:
	Projectile(Collider& collider, int damage, const Vector2& direction, float speed, float max_distance);
	void Update() override;

private:
	Collider& collider_;
	Vector2 direction_;
	int damage_;
	float speed_;
	float max_distance_;
	float distance_traveled_ = 0.f;
};

