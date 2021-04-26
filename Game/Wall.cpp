#include "Wall.h"

#include "../Opus/Collider.h"
#include "../Opus/Shape.h"
#include "../Opus/ShapeRenderer.h"

Wall::Wall() : Entity()
{
	AddComponent(ShapeRenderer(Shape::kSquare, 1, 1, 1, 1));
	AddComponent(Collider(0, Shape::kSquare, false, true));
	GetTransform().SetSize(100,100);
	GetTransform().SetPosition(500, 500);
}
