#pragma once

#include "../Opus/Core.h"

class SpriteRenderer;
class Item;
class Interactable;

class InventoryItem :
    public Entity
{
public:
	void Awake() override;
	void Initialize(const std::shared_ptr<Item>& item, const std::vector<int>& slot_indices = {});
	std::shared_ptr<Item> GetItem() const;
	std::vector<int> GetSlotIndices() const;
private:
	std::shared_ptr<Item> item_;
	std::vector<int> slot_indices_;

	std::shared_ptr<Interactable> interactable_;
	std::shared_ptr<SpriteRenderer> sr_;
};
