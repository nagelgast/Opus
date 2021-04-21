#include "Fireball.h"

#include "../Opus/Collider.h"
#include "../Opus/Input.h"
#include "Projectile.h"
#include "../Opus/ShapeRenderer.h"
#include "../Opus/Shape.h"
#include "../Opus/Transform.h"

Fireball::Fireball(const Vector2& start_pos, const Vector2& target_pos) : Entity()
{
	AddComponent(ShapeRenderer(Shape::kCircle, 1, 0, 0, 1));
	const auto collider = AddComponent(Collider(0, Shape::kCircle, false));
	GetTransform().SetSize(20,20);
	GetTransform().SetPosition(start_pos);

	const auto delta = target_pos - start_pos;
	const auto direction = delta.GetNormalized();
	AddComponent(Projectile(*collider, 10, direction, 200, 400));
}
