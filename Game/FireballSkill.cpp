#include "FireballSkill.h"

#include "../Opus/Input.h"
#include "Fireball.h"

void FireballSkill::Trigger(PlayerSkillHandler& psh)
{
	const auto player_pos = psh.entity_->GetTransform().GetPosition();
	auto fireball = psh.entity_->Instantiate<Fireball>(player_pos);

	fireball->Initialize(psh.entity_->GetInput().mouse_world_pos);
	fireball->GetTransform().CenterOrigin();
	fireball->SetName("Fireball");
}

float FireballSkill::GetCastTime()
{
	return 0.75f;
}
