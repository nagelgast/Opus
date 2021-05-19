#include "PlayerInventoryScreen.h"


#include "Inventory.h"
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

	player_inventory_ = Instantiate<Inventory>();
	auto& inv_trans = player_inventory_->GetTransform();
	inv_trans.SetParent(&GetTransform());
	inv_trans.SetLocalPosition({0, 250});
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
