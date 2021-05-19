#pragma once

#include "../Opus/Core.h"

class InventoryItem;
class Item;
class Inventory;

class InventorySlot : public Entity
{
public:
	void Awake() override;
	void SetItem(const std::shared_ptr<InventoryItem>& item);
	std::shared_ptr<InventoryItem> Take();
private:
	void HandleHoverEnter() const;
	void HandleHoverExit() const;

	std::shared_ptr<InventoryItem> item_;
	std::shared_ptr<Entity> highlight_;
};
