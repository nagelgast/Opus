#pragma once

#include "ItemTag.h"
#include "../Opus/Core.h"

class PlayerItemStorage;
class Item;
struct Color;
class ShapeRenderer;
class ScreenItem;
class Inventory;

class InventorySlot : public Entity
{
public:
	void Awake() override;
	void SetItem(ScreenItem& item);
	ScreenItem& GetItem() const;
	void ClearItem();
	void RemoveItem() const;
	bool HasItem() const;

	bool CanHold(Item& item) const;
	
	void SetRequiredTag(const ItemTag& tag);
	ItemTag GetRequiredTag() const;
	
	void HandleRelease();
	void SetEquippableHighlight() const;
	
	void EnableHighlight(Color color) const;
	void DisableHighlight() const;
private:
	ScreenItem* item_ = nullptr;
	Entity* highlight_ = nullptr;
	
	ItemTag required_tag_ = ItemTag::kNoTag;

	ShapeRenderer* shape_renderer_ = nullptr;

	PlayerItemStorage* storage_ = nullptr;
};
