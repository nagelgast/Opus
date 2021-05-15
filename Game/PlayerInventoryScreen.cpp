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

	auto inventory_entity = Instantiate();
	auto& inv_trans = inventory_entity->GetTransform();
	inv_trans.SetParent(&GetTransform());
	inv_trans.SetLocalPosition({50, 300});
	player_inventory_ = inventory_entity->AddComponent(Inventory());
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
