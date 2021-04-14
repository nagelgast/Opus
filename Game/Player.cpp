#include "Player.h"

#include "FireballSkill.h"
#include "PlayerController.h"
#include "PlayerSkillHandler.h"
#include "../Opus/Shape.h"
#include "../Opus/SpriteRenderer.h"

Player::Player() : Entity()
{
	AddComponent(SpriteRenderer("Sprites/chars/gabe/gabe-idle-run.png", 0, 0, 24, 24));
	SetShape(Shape::kSquare);
	SetSize(100, 100);

	AddComponent(PlayerController(200, 400));
	auto fireball = FireballSkill();
	const auto psh = PlayerSkillHandler(fireball);
	AddComponent(psh);

	layer_ = 0;
}
