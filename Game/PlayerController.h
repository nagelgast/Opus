#pragma once

#include "PlayerSkillHandler.h"
#include "../Opus/Core.h"

class Targetable;
class TargetingSystem;

class PlayerController final :
    public Component
{
public:
	PlayerController(std::shared_ptr<TargetingSystem> targeting_system, float walk_speed, float run_speed);
	void FixedUpdate() override;

	std::shared_ptr<PlayerSkillHandler> psh_;
private:
	std::shared_ptr<Targetable> target_;
	std::shared_ptr<TargetingSystem> targeting_system_;
	Vector2 target_pos_ = {0,0};
	float walk_speed_ = 0;
	float run_speed_ = 0;

	bool direct_control_ = false;
};
