#include "DefaultAttack.h"

#include <iostream>


#include "Health.h"
#include "../Opus/Collider.h"
#include "../Opus/Physics.h"

const float kDefaultAttackSpeed = 1.2f;
//const int kDefaultAttackRange = 6;
const int kDefaultAttackRange = 120;
const int kDefaultAttackMinDmg = 2;
const int kDefaultAttackMaxDmg = 6;


DefaultAttack::DefaultAttack()
{
	cast_time_ = 1 / kDefaultAttackSpeed;
}

void DefaultAttack::Cast()
{
	// Find target
	// Collider other;
	//
	// auto* health = other.entity_->GetComponent<Health>();
	// if (health)
	// {
	// 	const auto damage = rand() % (kDefaultAttackMaxDmg - kDefaultAttackMinDmg) + kDefaultAttackMinDmg;
	// 	health->TakeDamage(damage);
	// }
}

float DefaultAttack::GetCastTime()
{
	return cast_time_;
}

float DefaultAttack::GetRange()
{
	return kDefaultAttackRange;
}
