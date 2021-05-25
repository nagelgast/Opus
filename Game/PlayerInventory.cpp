#include "PlayerInventory.h"

#include <iostream>


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
		
		const auto success = inventory_->TryAutoAddItem(item);
		if(!success)
		{
			// TODO Give feedback that inventory is full
			std::cout << "Too. Much. Clutter.\n";
		}
	}
}
