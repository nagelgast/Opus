#pragma once

#include "../Opus/Core.h"

class ActiveSkill;

class PlayerSkillHandler final : public Component
{
public:
	~PlayerSkillHandler() override;
	
	void SetActiveSkill(ActiveSkill* active_skill);
	void Update() override;
	bool IsCasting() const;
	Vector2 GetTargetPosition() const;

private:
	float remaining_cast_time_ = 0;
	Vector2 target_position_;

	// TODO Replace with smart ptr or ref
	ActiveSkill* active_skill_ = nullptr;
};
