#include "FireballSkill.h"

#include "Fireball.h"

#include "../Opus/Input.h"

void FireballSkill::Trigger(const PlayerSkillHandler& psh)
{
	const auto player_pos = psh.entity_->GetTransform().GetPosition();
	psh.entity_->AddEntity(Fireball(player_pos, psh.entity_->GetInput().mouse_world_pos));
}
