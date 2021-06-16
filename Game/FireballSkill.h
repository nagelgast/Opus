#pragma once

#include "ActiveSkill.h"
#include "PlayerSkillHandler.h"

class FireballSkill : public ActiveSkill
{
public:
	explicit FireballSkill(const PlayerSkillHandler& psh);

	void Cast() override;

	float GetCastTime() override;
	float GetRange() override;
};

