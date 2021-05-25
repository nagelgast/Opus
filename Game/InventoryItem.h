#pragma once

#include "../Opus/Core.h"

struct Color;
class InventorySlot;
class SpriteRenderer;
class Item;
class Interactable;

class InventoryItem :
    public Entity
{
public:
	void Awake() override;
	void Initialize(const std::shared_ptr<InventoryItem>& self, const std::shared_ptr<Item>& item, const std::vector<std::shared_ptr<InventorySlot>>& slots);
	std::shared_ptr<Item> Take();
	std::shared_ptr<Item> GetItem() const;

	void SetHighlight(Color color);

private:
	std::shared_ptr<InventoryItem> self_;
	
	std::shared_ptr<Item> item_;
	std::vector<std::shared_ptr<InventorySlot>> slots_;

	std::shared_ptr<Interactable> interactable_;
	std::shared_ptr<SpriteRenderer> sr_;
};
