#pragma once
#include "ActiveSkill.h"

class DefaultAttack : public ActiveSkill
{
public:
	DefaultAttack();
	void Cast() override;

	float GetCastTime() override;
	float GetRange() override;
private:
	float cast_time_;
};

