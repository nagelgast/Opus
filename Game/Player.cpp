#include "Player.h"


#include "DefaultAttack.h"
#include "FireballSkill.h"
#include "MouseHandler.h"
#include "PlayerController.h"
#include "PlayerSkillHandler.h"

#include "../Opus/SpriteRenderer.h"
#include "../Opus/RectCollider.h"

void Player::Awake()
{
	const Sprite sprite { "Sprites/chars/gabe/gabe-idle-run.png", {0, 0, 24, 24}};
	const auto sr = AddComponent(SpriteRenderer());
	sr.SetSprite(sprite);
	
	const auto collider = AddComponent(RectCollider({0,0,1,1}, 1, false, false));
	GetTransform().SetScale(100, 100);

	auto pc = AddComponent(PlayerController(200, 400));

	auto& psh = AddComponent(PlayerSkillHandler());

	// TODO Store skill references properly
	auto* const default_attack = new DefaultAttack();
	psh.SetActiveSkill(default_attack);

	// auto* const fireball = new FireballSkill(&psh);
	// psh.SetActiveSkill(fireball);
}
