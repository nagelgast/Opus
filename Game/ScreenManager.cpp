#include "ScreenManager.h"


#include "PlayerInventoryScreen.h"
#include "../Opus/Input.h"
#include "../Opus/Transform.h"

void ScreenManager::Awake()
{
	player_inventory_screen_ = Instantiate<PlayerInventoryScreen>();
	auto& transform = player_inventory_screen_->GetTransform();
	transform.SetPosition({1024-(350/2), 768/2});
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
