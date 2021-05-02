#pragma once

#include "../Opus/Core.h"

class FireballSkill;

class PlayerSkillHandler final : public Component
{
public:
	explicit PlayerSkillHandler(FireballSkill& active_skill);

	void Update() override;
	bool IsCasting() const;

private:
	float remaining_cast_time_;
	FireballSkill& active_skill_;
};
