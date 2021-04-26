#include "FireballSkill.h"

#include "Fireball.h"

#include "../Opus/Input.h"

void FireballSkill::Trigger(const PlayerSkillHandler& psh)
{
	const auto player_pos = psh.entity_->GetTransform().GetPosition();
	const auto fireball = psh.entity_->Instantiate(Fireball(player_pos, psh.entity_->GetInput().mouse_world_pos));
	fireball->SetName("Fireball");
}
