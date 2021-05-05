#pragma once

#include "PlayerSkillHandler.h"

class FireballSkill
{
public:
	void Trigger(PlayerSkillHandler&) ;
	float GetCastTime();
};

