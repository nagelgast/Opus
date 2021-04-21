#pragma once

#include "../Opus/Collider.h"
#include "../Opus/Component.h"
#include "../Opus/Vector2.h"

class PlayerController final :
    public Component
{
public:
	PlayerController(Collider& collider, float walk_speed, float run_speed);
	void Update() override;
private:
	Collider& collider_;
	Vector2 target_pos_ = {0,0};
	float walk_speed_ = 0;
	float run_speed_ = 0;

	bool direct_control_ = false;
};
