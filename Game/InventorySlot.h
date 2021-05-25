#pragma once

#include "ItemTag.h"
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
	void SetItem(std::shared_ptr<InventoryItem> item);
	std::shared_ptr<InventoryItem> GetItem();
	void ClearItem();
	bool HasItem() const;

	void SetRequiredTag(ItemTag tag);
	ItemTag GetRequiredTag() const;

	void EnableHighlight(Color color) const;
	void DisableHighlight() const;
private:
	std::shared_ptr<InventoryItem> item_;
	std::shared_ptr<Entity> highlight_;
	ItemTag required_tag_ = ItemTag::no_tag;

	std::shared_ptr<ShapeRenderer> shape_renderer_;
};
