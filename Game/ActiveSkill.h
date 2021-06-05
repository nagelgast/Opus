#pragma once

class ActiveSkill
{
public:
	virtual ~ActiveSkill() = default;
	virtual void Cast() = 0;
	virtual float GetCastTime() = 0;
	virtual float GetRange() = 0;
};
