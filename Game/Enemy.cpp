#include "Enemy.h"

#include "Health.h"
#include "Loot.h"

#include "../Opus/Shape.h"
#include "../Opus/Collider.h"
#include "../Opus/SpriteRenderer.h"

void Enemy::Awake()
{
	const Sprite sprite{"Sprites/mobs/slime-blue.png", {0, 8, 16, 16}};
	auto sr = AddComponent(SpriteRenderer());
	sr.SetSprite(sprite);
	AddComponent(Collider(0, Shape::kSquare, false, false));
	GetTransform().SetScale(32, 32);

	AddComponent(Health(1));
	AddComponent(Loot());
}
