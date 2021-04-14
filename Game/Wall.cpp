#include "Wall.h"

#include "../Opus/ColliderComponent.h"
#include "../Opus/Shape.h"
#include "../Opus/ShapeRenderer.h"

Wall::Wall() : Entity()
{
	AddComponent(ShapeRenderer(Shape::kSquare, 1, 1, 1, 1));
	SetShape(Shape::kSquare);
	SetSize(100,100);
	SetPosition(500, 500);

	AddComponent(ColliderComponent());

	layer_ = 2;
}
