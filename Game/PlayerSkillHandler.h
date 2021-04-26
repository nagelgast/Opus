#pragma once

#include "../Opus/Core.h"

class FireballSkill;

class PlayerSkillHandler final : public Component
{
public:
	explicit PlayerSkillHandler(FireballSkill& active_skill);

	void Update() override;

private:
	FireballSkill& active_skill_;
};
