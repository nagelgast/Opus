#pragma once

#include "../Opus/Core.h"

struct Color;
class ShapeRenderer;
class InventoryItem;
class Item;
class Inventory;

class InventorySlot : public Entity
{
public:
	void Awake() override;
	void SetItem(const std::shared_ptr<InventoryItem>& item);
	InventoryItem& GetItem() const;
	void ClearItem();
	bool HasItem() const;

	void EnableHighlight(Color color) const;
	void DisableHighlight() const;
private:
	std::shared_ptr<InventoryItem> item_;
	std::shared_ptr<Entity> highlight_;

	std::shared_ptr<ShapeRenderer> shape_renderer_;
};
