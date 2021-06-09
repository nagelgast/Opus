#pragma once

#include "../Opus/Core.h"

#include "Inventory.h"
#include "MouseSlot.h"
#include "PlayerInventoryScreen.h"
#include "../Opus/Service.h"

// TODO Move to global settings
const int kInventorySlotSize = 25;
const Color kItemSlotColor = { 0, 0, 0.5, 0.5 };
const Color kAvailableSlotColor = { 0, 0.5, 0, 0.5 };
const Color kPickupSlotColor = { 0.5, 0.5, 0, 0.5 };
const Color kUnavailableSlotColor = { 0.5, 0, 0, 0.5 };

class PlayerInventory : public Service
{
public:
	void Initialize(MouseSlot& mouse, PlayerInventoryScreen& screen);

	bool IsHoldingItem() const;
	ItemSize GetHeldItemSize() const;
	void HandleEquipmentRelease(InventorySlot& slot);
	void ReleasedOverInventorySlot(const int index, const std::vector<int>& hovered_slot_indices);
	void PickUpItem(std::unique_ptr<Item> item);
	std::unique_ptr<Item> Equip(InventorySlot& equipment_slot, std::unique_ptr<Item> item);
	bool CanEquipHeldItem(const InventorySlot& slot) const;
private:
	// Data
	std::unique_ptr<Inventory> inventory_;
	
	//std::map<std::string, std::unique_ptr<Item>> equipment_;
	std::unique_ptr<Item> helmet_;
	std::unique_ptr<Item> weapon_;
	std::unique_ptr<Item> armour_;

	
	// UI
	PlayerInventoryScreen* screen_ = nullptr;
	MouseSlot* mouse_slot_ = nullptr;
	// std::shared_ptr<EquipmentInventory>
};
