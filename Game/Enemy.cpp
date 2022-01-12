#include "Enemy.h"

#include "Health.h"
#include "Loot.h"

#include "../Opus/RectCollider.h"
#include "../Opus/SpriteRenderer.h"
#include "../Opus/Animation.h"

void Enemy::Awake()
{
	const Sprite sprite{"Sprites/mobs/slime-blue.png", {0, 8, 16, 16}};
	auto sr = AddComponent(SpriteRenderer());
	sr.SetSprite(sprite);

	AddComponent(Animation(4, 1.f / 8));

	auto& col = AddComponent(RectCollider(0, false, false));
	col.SetSize({16, 16});
	GetTransform().SetScale(5, 5);

	AddComponent(Health(1));
	AddComponent(Loot());
}
