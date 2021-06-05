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

private:
	float remaining_cast_time_ = 0;

	// TODO Replace with smart ptr or ref
	ActiveSkill* active_skill_ = nullptr;
};
