#pragma once
#include <map>

#include "../Opus/Core.h"

class InventoryItem;
class Item;

class Inventory : public Component
{
public:
	void AddItem(const std::shared_ptr<Item>& item);

private:
	int rows_ = 5;
	int columns_ = 12;

	std::map<int, std::shared_ptr<InventoryItem>> items_;
};
