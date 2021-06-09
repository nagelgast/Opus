#pragma once

#include "ActiveSkill.h"
#include "PlayerSkillHandler.h"

class FireballSkill : public ActiveSkill
{
public:
	FireballSkill(PlayerSkillHandler* psh);
	void Cast() override;

	float GetCastTime() override;
	float GetRange() override;
private:
	PlayerSkillHandler* psh_ = nullptr;
};

