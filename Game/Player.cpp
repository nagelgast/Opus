#include "Player.h"


#include "DefaultAttack.h"
#include "FireballSkill.h"
#include "MouseHandler.h"
#include "PlayerController.h"
#include "PlayerSkillHandler.h"

#include "../Opus/RectCollider.h"

#include "PlayerAnimator.h"

void Player::Awake()
{
	AddComponent(PlayerAnimator());

	auto& collider = AddComponent(RectCollider(1, false, false));
	
	GetTransform().SetScale(5, 5);

	auto pc = AddComponent(PlayerController(200, 400));

	auto& psh = AddComponent(PlayerSkillHandler());

	// TODO Store skill references properly
	auto* const default_attack = new DefaultAttack(psh);
	psh.SetActiveSkill(default_attack);

	// auto* const fireball = new FireballSkill(psh);
	// psh.SetActiveSkill(fireball);
}
