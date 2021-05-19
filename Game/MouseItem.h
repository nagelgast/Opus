#pragma once

#include "../Opus/Core.h"

class SpriteRenderer;
class Item;

class MouseItem final :
	public Entity
{
public:
	void Awake() override;
	
	bool TryAddItem(std::shared_ptr<Item> item);
	
	bool TryDrop(Vector2 position);
	void Drop(Vector2 position);
	bool HasItem() const;
	void Update() override;
private:
	std::shared_ptr<Item> item_;
	std::shared_ptr<SpriteRenderer> renderer_;

	// TODO Change when implementing town
	const bool can_drop_items_ = true;
};
