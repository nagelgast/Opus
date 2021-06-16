#pragma once
#include "ActiveSkill.h"

class DefaultAttack : public ActiveSkill
{
public:
	explicit DefaultAttack(const PlayerSkillHandler& psh);

	void Cast() override;

	float GetCastTime() override;
	float GetRange() override;
private:
	float cast_time_;
};

