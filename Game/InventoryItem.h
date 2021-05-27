#pragma once

#include "Item.h"
#include "../Opus/Core.h"

struct Color;
class InventorySlot;
class SpriteRenderer;
class Interactable;

class InventoryItem :
    public Entity
{
public:
	void Awake() override;
	void Initialize(std::unique_ptr<Item> item, const std::vector<InventorySlot*>& slots);
	std::unique_ptr<Item> TakeItem();
	Item& GetItem() const;

	void SetHighlight(Color color);
private:
	std::unique_ptr<Item> item_;
	std::vector<InventorySlot*> slots_;

	Interactable* interactable_ = nullptr;
	SpriteRenderer* sr_= nullptr;
};
