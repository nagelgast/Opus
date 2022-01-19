#pragma once

#include "Item.h"
#include "../Opus/Core.h"

struct Color;
class InventorySlot;
class SpriteRenderer;
class Interactable;

class ScreenItem :
    public Component
{
public:
	void Awake() override;
	void Initialize(Item& item, const std::vector<InventorySlot*>& slots);
	Item& GetItem() const;

	void Remove();
	
	void SetHighlight(Color color);
private:
	Item* item_ = nullptr;
	std::vector<InventorySlot*> slots_;

	Interactable* interactable_ = nullptr;
	SpriteRenderer* sr_= nullptr;
};
