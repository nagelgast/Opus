#include "DefaultAttack.h"



#include "Health.h"
#include "PlayerSkillHandler.h"
#include "../Opus/Input.h"
#include "../Opus/Physics.h"

const float kDefaultAttackSpeed = 1.2f;
//const int kDefaultAttackRange = 6;
const int kDefaultAttackRange = 120;
const int kDefaultAttackMinDmg = 2;
const int kDefaultAttackMaxDmg = 6;

DefaultAttack::DefaultAttack(const PlayerSkillHandler& psh) : ActiveSkill(psh)
{
	cast_time_ = 1 / kDefaultAttackSpeed;
}

void DefaultAttack::Cast()
{
	auto* collider = Physics::GetColliderAtPosition(psh_.GetTargetPosition(), 0);
	if(!collider) return;

	auto* health = collider->entity_->GetComponent<Health>();
	if (health)
	{
		const auto damage = rand() % (kDefaultAttackMaxDmg - kDefaultAttackMinDmg) + kDefaultAttackMinDmg;
		health->TakeDamage(damage);
	}
}

float DefaultAttack::GetCastTime()
{
	return cast_time_;
}

float DefaultAttack::GetRange()
{
	return kDefaultAttackRange;
}
