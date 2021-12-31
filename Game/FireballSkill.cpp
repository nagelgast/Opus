#include "FireballSkill.h"

#include "../Opus/Input.h"
#include "Fireball.h"

FireballSkill::FireballSkill(const PlayerSkillHandler& psh) : ActiveSkill(psh)
{
}

void FireballSkill::Cast()
{
	const auto player_pos = psh_.entity_->GetTransform().GetPosition();
	auto& fireball = psh_.entity_->Instantiate<Fireball>(player_pos);

	fireball.Initialize(psh_.GetTargetPosition());
	fireball.SetName("Fireball");
}

float FireballSkill::GetCastTime()
{
	return 0.75f;
}

float FireballSkill::GetRange()
{
	return 1200;
}
