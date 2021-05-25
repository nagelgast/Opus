#include "PlayerInventory.h"

#include <iostream>

#include "Item.h"

PlayerInventory& PlayerInventory::GetInstance()
{
	return *instance_;
}

void PlayerInventory::Initialize(const std::shared_ptr<MouseItem>& mouse,
                                 const std::shared_ptr<PlayerInventoryScreen>& screen)
{
	instance_ = this;
	
	mouse_item_ = mouse;
	screen_ = screen;

	inventory_ = Instantiate<Inventory>(&screen_->GetTransform());
	auto& inv_trans = inventory_->GetTransform();
	inv_trans.SetLocalPosition({ 0, 250 });

	inventory_->Initialize(mouse_item_);
}

void PlayerInventory::PickUpItem(const std::shared_ptr<Item>& item) const
{
	if(screen_->IsOpen())
	{
		mouse_item_->TryAddItem(item);
	}
	else
	{
		//if(can_go_to_empty_gear_slot) Equip()
		
		const auto success = inventory_->TryAutoAddItem(item);
		if(!success)
		{
			std::cout << "Too. Much. Clutter.\n";
		}
	}
}

PlayerInventory* PlayerInventory::instance_;