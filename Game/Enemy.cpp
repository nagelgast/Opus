#include "Enemy.h"

#include "../Opus/Shape.h"
#include "Health.h"
#include "../Opus/SpriteRenderer.h"

Enemy::Enemy()
{
	AddComponent(SpriteRenderer("Sprites/mobs/slime-blue.png", 0, 8, 16, 16));
	SetShape(Shape::kSquare);
	SetSize(32,32);

	AddComponent(Health(100));

	layer_ = 2;
}
