#pragma once

#include "../Opus/Core.h"

#include "Inventory.h"
#include "MouseSlot.h"
#include "PlayerInventoryScreen.h"
#include "../Opus/Service.h"

class PlayerInventory : public Service
{
public:
	void Initialize(MouseSlot& mouse, PlayerInventoryScreen& screen);
	void PickUpItem(std::unique_ptr<Item> item) const;
	std::unique_ptr<Item> Equip(InventorySlot& equipment_slot, std::unique_ptr<Item> item);
private:
	// Data
	Inventory* inventory_ = nullptr;
	//std::map<std::string, std::unique_ptr<Item>> equipment_;
	std::unique_ptr<Item> helmet_;
	std::unique_ptr<Item> weapon_;
	std::unique_ptr<Item> armour_;

	
	// UI
	PlayerInventoryScreen* screen_ = nullptr;
	MouseSlot* mouse_slot_ = nullptr;
	// std::shared_ptr<EquipmentInventory>

};
