#pragma once

#include "../Opus/Core.h"

class Projectile;

class Fireball final : public Entity
{
public:
	void Awake() override;
	void Initialize(const Vector2& target_pos);
private:
	std::shared_ptr<Projectile> projectile_;
};

