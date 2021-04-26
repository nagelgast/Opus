#pragma once

#include "PlayerSkillHandler.h"

class Skill
{
public:
	virtual void Trigger(const PlayerSkillHandler&);
};
