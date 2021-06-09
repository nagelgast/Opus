#pragma once

#include "../Opus/Core.h"

#include "Inventory.h"
#include "MouseSlot.h"
#include "PlayerInventoryScreen.h"
#include "../Opus/Service.h"

class EquipmentSlot;
// TODO Move to global settings
const int kInventorySlotSize = 25;
const Color kItemSlotColor = { 0, 0, 0.5, 0.5 };
const Color kAvailableSlotColor = { 0, 0.5, 0, 0.5 };
const Color kPickupSlotColor = { 0.5, 0.5, 0, 0.5 };
const Color kUnavailableSlotColor = { 0.5, 0, 0, 0.5 };

class PlayerItemStorage : public Service
{
public:
	void Initialize(MouseSlot& mouse, PlayerInventoryScreen& screen);

	bool IsHoldingItem() const;
	ItemSize GetHeldItemSize() const;
	void HandleEquipmentRelease(EquipmentSlot& slot);
	void HandleInventoryRelease(int index, const std::vector<int>& hovered_slot_indices) const;
	void PickUpItem(std::unique_ptr<Item> item) const;
	std::unique_ptr<Item> Equip(EquipmentSlot& equipment_slot, std::unique_ptr<Item> item);
	bool CanEquipHeldItem(const EquipmentSlot& slot) const;
private:
	// Data
	std::unique_ptr<Inventory> inventory_;
	std::map<ItemTag, std::unique_ptr<Item>> equipment_;
	
	// UI
	PlayerInventoryScreen* screen_ = nullptr;
	MouseSlot* mouse_slot_ = nullptr;
};
