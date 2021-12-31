#include "Wall.h"

#include "../Opus/RectCollider.h"
#include "../Opus/Shape.h"
#include "../Opus/ShapeRenderer.h"

void Wall::Awake()
{
	AddComponent(ShapeRenderer(Shape::kSquare, {0.8f, 0.8f, 0.8f}));
	AddComponent(RectCollider(0, false, true));
	GetTransform().SetScale(100,100);
}
