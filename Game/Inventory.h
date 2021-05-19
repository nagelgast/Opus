#pragma once
#include <map>

#include "../Opus/Core.h"

class MouseItem;
class InventoryItem;
class Item;

class Inventory : public Entity
{
public:
	void Initialize(const std::shared_ptr<MouseItem>& mouse_item);
	void Awake() override;
	void AddItem(const std::shared_ptr<Item>& item);

private:
	int rows_ = 5;
	int columns_ = 12;

	void HandlePress();

	std::shared_ptr<MouseItem> mouse_item_;
	
	std::map<int, std::shared_ptr<InventoryItem>> items_;
};
