#include "ScreenManager.h"


#include "PlayerInventoryScreen.h"
#include "../Opus/Input.h"
#include "../Opus/Transform.h"

void ScreenManager::Awake()
{
	player_inventory_screen_ = &Instantiate<PlayerInventoryScreen>({ 1024 - 350, 0});
	player_inventory_screen_->SetName("Player Inventory Screen");
	player_inventory_screen_->Close();
}

void ScreenManager::Update()
{
	const auto& input = GetInput();
	if(input.inventory.pressed)
	{
		player_inventory_screen_->Open();
	}

	if(input.close_all_ui.pressed)
	{
		player_inventory_screen_->Close();
	}
}

bool ScreenManager::CheckIsInScreenSpace(const Vector2 position) const
{
	// TODO Implement properly
	if(player_inventory_screen_->IsOpen())
	{
		return position.x > 1024 - 350;
	}
	
	return false;
}
