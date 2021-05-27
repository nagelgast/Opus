#pragma once

#include "ItemTag.h"
#include "../Opus/Core.h"

struct Item;
struct Color;
class ShapeRenderer;
class InventoryItem;
class Inventory;

class InventorySlot : public Entity
{
public:
	void Awake() override;
	void SetItem(InventoryItem& item);
	InventoryItem& GetItem() const;
	void ClearItem();
	bool HasItem() const;

	bool CanHold(Item& item) const;
	
	void SetRequiredTag(ItemTag tag);
	ItemTag GetRequiredTag() const;

	void EnableHighlight(Color color) const;
	void DisableHighlight() const;
private:
	InventoryItem* item_ = nullptr;
	Entity* highlight_ = nullptr;
	
	ItemTag required_tag_ = ItemTag::no_tag;

	ShapeRenderer* shape_renderer_ = nullptr;
};
