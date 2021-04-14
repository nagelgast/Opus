#include "FireballSkill.h"

#include "ColliderComponent.h"
#include "Entity.h"
#include "Fireball.h"
#include "Input.h"

void FireballSkill::Trigger(const PlayerSkillHandler& psh)
{
	const auto player_pos = psh.entity_->GetPosition();
	psh.entity_->AddEntity(Fireball(player_pos, psh.entity_->GetInput().mouse_pos));
}
