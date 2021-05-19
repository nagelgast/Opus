#pragma once
#include <map>

#include "../Opus/Core.h"

class InventorySlot;
class MouseItem;
class InventoryItem;
class Item;

class Inventory : public Entity
{
public:
	void Initialize(const std::shared_ptr<MouseItem>& mouse_item);
	void Awake() override;
	void AddItem(const std::shared_ptr<Item>& item);
	void AddItem(const std::shared_ptr<Item>& item, const std::shared_ptr<InventorySlot>& slot) const;
	void HandleRelease(int index);

private:
	std::shared_ptr<InventoryItem> SpawnInventoryItem(const std::shared_ptr<Item>& item) const;
	int rows_ = 5;
	int columns_ = 12;

	std::shared_ptr<MouseItem> mouse_item_;
	
	std::vector<std::shared_ptr<InventorySlot>> slots_;
};
