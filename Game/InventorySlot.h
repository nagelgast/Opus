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
	InventoryItem& GetItem();
	bool HasItem() const;
	std::shared_ptr<InventoryItem> Take();

	void EnableHighlight();
	void DisableHighlight();
private:
	std::shared_ptr<InventoryItem> item_;
	std::shared_ptr<Entity> highlight_;
};
