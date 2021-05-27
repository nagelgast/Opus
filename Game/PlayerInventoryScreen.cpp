#include "PlayerInventoryScreen.h"


#include "Inventory.h"
#include "../Opus/Shape.h"
#include "../Opus/ShapeRenderer.h"
#include "../Opus/Transform.h"

void PlayerInventoryScreen::Awake()
{
	background_ = &Instantiate(GetTransform());
	background_->AddComponent(ShapeRenderer(Shape::kSquare, {0.8f, 0.8f, 0.8f}, false));

	auto& transform = background_->GetTransform();
	transform.SetScale(350, 768);
}

void PlayerInventoryScreen::Open()
{
	if(is_open_)
	{
		Close();
	}
	else
	{
		is_open_ = true;
		SetVisible(true);
	}
}

void PlayerInventoryScreen::Close()
{
	is_open_ = false;
	SetVisible(false);
}

bool PlayerInventoryScreen::IsOpen() const
{
	return is_open_;
}
