#include "PlayerInventory.h"

#include "Item.h"

void PlayerInventory::PickUpItem(std::shared_ptr<Item> item)
{
	if(screen_->IsOpen())
	{
		mouse_item_->TryAddItem(item);
	}
	else
	{
		//if(can_go_to_empty_gear_slot) Equip()
		
		inventory_->AddItem(item);
	}
}
