#pragma once

#include "../Opus/Core.h"

class PlayerItemStorage;
class Item;
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
	void RemoveItem();
	bool HasItem() const;

	bool CanHold(Item& item) const;
	
	void SetRequiredTag(const std::string& tag);
	std::string GetRequiredTag() const;

	void SetEquippableHighlight() const;
	
	void EnableHighlight(Color color) const;
	void DisableHighlight() const;
private:
	InventoryItem* item_ = nullptr;
	Entity* highlight_ = nullptr;
	
	std::string required_tag_ = "no_tag";

	ShapeRenderer* shape_renderer_ = nullptr;

	PlayerItemStorage* player_inventory_ = nullptr;
};
