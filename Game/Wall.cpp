#include "Wall.h"

#include "../Opus/RectCollider.h"
#include "../Opus/Shape.h"
#include "../Opus/ShapeRenderer.h"

void Wall::Awake()
{
	AddComponent(ShapeRenderer(Shape::kSquare, {1, 1, 1}));
	AddComponent(RectCollider({0,0,1,1}, 0, false, true));
	GetTransform().SetScale(100,100);
}
