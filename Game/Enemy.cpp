#include "Enemy.h"

#include "Health.h"
#include "Loot.h"

#include "../Opus/RectCollider.h"
#include "../Opus/SpriteRenderer.h"

void Enemy::Awake()
{
	const Sprite sprite{"Sprites/mobs/slime-blue.png", {0, 8, 16, 16}};
	auto sr = AddComponent(SpriteRenderer());
	sr.SetSprite(sprite);
	AddComponent(RectCollider({0, 0, 1, 1}, 0, false, false));
	GetTransform().SetScale(32, 32);

	AddComponent(Health(1));
	AddComponent(Loot());
}
