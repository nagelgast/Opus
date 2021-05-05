#include "Player.h"

#include "FireballSkill.h"
#include "PlayerController.h"
#include "PlayerSkillHandler.h"
#include "TargetingSystem.h"

#include "../Opus/Shape.h"
#include "../Opus/SpriteRenderer.h"
#include "../Opus/Collider.h"

Player::Player() : Entity()
{
	const Sprite sprite { "Sprites/chars/gabe/gabe-idle-run.png", {0, 0, 24, 24}};
	AddComponent(SpriteRenderer(sprite));
	const auto collider = AddComponent(Collider(1, Shape::kSquare, false, false));
	GetTransform().SetSize(100, 100);

	auto ts = AddComponent(TargetingSystem());

	auto pc = AddComponent(PlayerController(ts, 200, 400));
	auto fireball = FireballSkill();

	const auto psh = AddComponent(PlayerSkillHandler(fireball));

	pc->psh_ = psh;
}
