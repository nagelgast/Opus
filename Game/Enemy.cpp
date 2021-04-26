#include "Enemy.h"

#include "../Opus/Shape.h"
#include "Health.h"
#include "../Opus/Collider.h"
#include "../Opus/SpriteRenderer.h"
#include "../Opus/Transform.h"

Enemy::Enemy()
{
	AddComponent(SpriteRenderer("Sprites/mobs/slime-blue.png", 0, 8, 16, 16));
	AddComponent(Collider(0, Shape::kSquare, false, false));
	GetTransform().SetSize(32,32);

	AddComponent(Health(100));
}
