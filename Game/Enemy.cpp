#include "Enemy.h"

#include "Health.h"
#include "Loot.h"

#include "../Opus/Shape.h"
#include "../Opus/Collider.h"
#include "../Opus/SpriteRenderer.h"

Enemy::Enemy()
{
	const Sprite sprite{"Sprites/mobs/slime-blue.png", {0, 8, 16, 16}};
	AddComponent(SpriteRenderer(sprite));
	AddComponent(Collider(0, Shape::kSquare, false, false));
	GetTransform().SetSize(32, 32);

	AddComponent(Health(100));
	AddComponent(Loot());
}
