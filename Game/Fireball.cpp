#include "Fireball.h"

#include "Projectile.h"

#include "../Opus/Collider.h"
#include "../Opus/ShapeRenderer.h"
#include "../Opus/Shape.h"

void Fireball::Awake()
{
	AddComponent(ShapeRenderer(Shape::kCircle, 1, 0, 0, 1));
	const auto collider = AddComponent(Collider(2, Shape::kSquare, true, false));
	GetTransform().SetSize(20,20);
	projectile_ = AddComponent(Projectile(10, 200, 400));
}

void Fireball::Initialize(const Vector2& start_pos, const Vector2& target_pos)
{
	GetTransform().SetPosition(start_pos);
	const auto delta = target_pos - start_pos;
	const auto direction = delta.GetNormalized();
	projectile_->SetDirection(direction);
}
