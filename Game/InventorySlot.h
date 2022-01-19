#pragma once

#include "ItemTag.h"
#include "../Opus/Core.h"

class Interactable;
class PlayerItemStorage;
class Item;
struct Color;
class ShapeRenderer;
class ScreenItem;
class Inventory;

class InventorySlot : public Component
{
public:
	void SetItem(ScreenItem& item);
	ScreenItem& GetItem() const;
	void ClearItem();
	void RemoveItem() const;
	bool HasItem() const;

	void EnableHighlight(Color color) const;
	void DisableHighlight() const;

protected:
	void Awake() override;
	PlayerItemStorage* storage_ = nullptr;
	Interactable* interactable_ = nullptr;
	ScreenItem* item_ = nullptr;

private:
	Entity* highlight_ = nullptr;
	ShapeRenderer* shape_renderer_ = nullptr;
};
