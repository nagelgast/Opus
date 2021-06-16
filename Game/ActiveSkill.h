#pragma once

class PlayerSkillHandler;

class ActiveSkill
{
public:
	explicit ActiveSkill(const PlayerSkillHandler& psh)
		: psh_(psh)
	{
	}

	virtual ~ActiveSkill() = default;
	virtual void Cast() = 0;
	virtual float GetCastTime() = 0;
	virtual float GetRange() = 0;
protected:
	const PlayerSkillHandler& psh_;
};
