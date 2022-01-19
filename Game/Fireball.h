#pragma once

#include "../Opus/Core.h"

class Projectile;

class Fireball final : public Component
{
public:
	void Awake() override;
	void Initialize(const Vector2& target_pos) const;
private:
	Projectile* projectile_ = nullptr;
};

