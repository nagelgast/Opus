#include "Player.h"


#include "DefaultAttack.h"
#include "MouseHandler.h"
#include "PlayerController.h"
#include "PlayerSkillHandler.h"

#include "../Opus/Shape.h"
#include "../Opus/SpriteRenderer.h"
#include "../Opus/Collider.h"

void Player::Awake()
{
	const Sprite sprite { "Sprites/chars/gabe/gabe-idle-run.png", {0, 0, 24, 24}};
	const auto sr = AddComponent(SpriteRenderer());
	sr.SetSprite(sprite);
	
	const auto collider = AddComponent(Collider(1, Shape::kSquare, false, false));
	GetTransform().SetScale(100, 100);

	auto pc = AddComponent(PlayerController(200, 400));

	auto& psh = AddComponent(PlayerSkillHandler());
	
	auto* const default_attack = new DefaultAttack();
	psh.SetActiveSkill(default_attack);
}
