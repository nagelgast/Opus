#include "PlayerInventoryScreen.h"

#include "../Opus/Shape.h"
#include "../Opus/ShapeRenderer.h"
#include "../Opus/Transform.h"

void PlayerInventoryScreen::Awake()
{
	background_ = Instantiate();
	background_->AddComponent(ShapeRenderer(Shape::kSquare, 0.8f, 0.8f, 0.8f, 1, false));
	auto& transform = background_->GetTransform();
	transform.SetParent(&GetTransform());
	transform.SetSize(350, 768);
}

void PlayerInventoryScreen::Open()
{
	background_->SetVisible(true);
}

void PlayerInventoryScreen::Close()
{
	background_->SetVisible(false);
}
