#pragma once

#include "Inventory.h"
#include "Item.h"
#include "../Opus/Core.h"

class SpriteRenderer;

class MouseSlot final :
	public Entity
{
public:
	void Awake() override;
	
	bool SetItem(std::unique_ptr<Item> item);
	
	bool TryDrop(Vector2 position);
	std::unique_ptr<Item> Take();
	Item& GetItem();
	bool HasItem() const;
	void Update() override;
private:
	void Drop(Vector2 position);
	void Clear() const;
	
	std::unique_ptr<Item> item_;
	SpriteRenderer* renderer_ = nullptr;

	// TODO Change when implementing town
	const bool can_drop_items_ = true;
};
