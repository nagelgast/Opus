#pragma once

#include "Component.h"
#include "Vector2.h"

class PlayerController final :
    public Component
{
public:
	PlayerController(float walk_speed, float run_speed);
	void Update() override;
private:
	Vector2 target_pos_ = {0,0};
	float walk_speed_ = 0;
	float run_speed_ = 0;

	bool direct_control_ = false;
};
