#include "Wall.h"

#include "../Opus/ColliderComponent.h"
#include "../Opus/Shape.h"
#include "../Opus/ShapeRenderer.h"
#include "../Opus/Transform.h"

Wall::Wall() : Entity()
{
	AddComponent(ShapeRenderer(Shape::kSquare, 1, 1, 1, 1));
	SetShape(Shape::kSquare);
	GetTransform().SetSize(100,100);
	GetTransform().SetPosition(500, 500);

	AddComponent(ColliderComponent());

	layer_ = 2;
}
