#pragma once

#include "../Opus/Core.h"

class PlayerAnimator;
class ActiveSkill;

class PlayerSkillHandler final : public Component
{
public:
	~PlayerSkillHandler() override;

	void Start() override;
	void SetActiveSkill(ActiveSkill* active_skill);
	void Update() override;
	bool IsCasting() const;
	Vector2 GetTargetPosition() const;

private:
	PlayerAnimator* anim_ = nullptr;

	float remaining_cast_time_ = 0;
	bool moving_to_target_ = false;
	Vector2 target_position_;
	
	// TODO Replace with smart ptr or ref
	ActiveSkill* active_skill_ = nullptr;
};
