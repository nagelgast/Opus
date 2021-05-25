#pragma once

#include "Inventory.h"
#include "../Opus/Core.h"

class SpriteRenderer;
class Item;

class MouseSlot final :
	public Entity
{
public:
	void Awake() override;
	
	bool SetItem(std::shared_ptr<Item> item);
	
	bool TryDrop(Vector2 position);
	std::shared_ptr<Item> Take();
	Item& GetItem();
	bool HasItem() const;
	void Update() override;
private:
	void Drop(Vector2 position);
	void Clear();
	
	std::shared_ptr<Item> item_;
	std::shared_ptr<SpriteRenderer> renderer_;

	// TODO Change when implementing town
	const bool can_drop_items_ = true;
};
