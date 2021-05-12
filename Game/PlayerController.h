#pragma once

#include "PlayerSkillHandler.h"
#include "../Opus/Core.h"

class Interactable;

class PlayerController final :
    public Component
{
public:
	PlayerController(float walk_speed, float run_speed);
	void FixedUpdate() override;

	std::shared_ptr<PlayerSkillHandler> psh_;
private:
	Interactable* target_ = nullptr;
	Vector2 target_pos_ = {0,0};
	float walk_speed_ = 0;
	float run_speed_ = 0;

	bool direct_control_ = false;
};
