#include "Fireball.h"

#include "ColliderComponent.h"
#include "Input.h"
#include "Projectile.h"
#include "ShapeRenderer.h"
#include "Shape.h"

Fireball::Fireball(const Vector2& start_pos, const Vector2& target_pos) : Entity()
{
	AddComponent(ShapeRenderer(Shape::kCircle, 1, 0, 0, 1));
	SetShape(Shape::kCircle);
	SetSize(20,20);
	SetPosition(start_pos);

	const auto delta = target_pos - start_pos;
	const auto direction = delta.GetNormalized();
	AddComponent(Projectile(10, direction, 200, 400));
	AddComponent(ColliderComponent());

	layer_ = 1;
}
