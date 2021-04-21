#include "FireballSkill.h"

#include "../Opus/Collider.h"
#include "../Opus/Entity.h"
#include "Fireball.h"
#include "../Opus/Input.h"
#include "../Opus/Transform.h"

void FireballSkill::Trigger(const PlayerSkillHandler& psh)
{
	const auto player_pos = psh.entity_->GetTransform().GetPosition();
	psh.entity_->AddEntity(Fireball(player_pos, psh.entity_->GetInput().mouse_world_pos));
}
