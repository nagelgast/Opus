#pragma once

#include "../Opus/Core.h"

class SpriteRenderer;
class Item;

class MouseItem final :
	public Entity
{
public:
	explicit MouseItem();
	
	bool TrySetItem(std::shared_ptr<Item> item);
	bool HasItem() const;
	void Update() override;
private:
	std::shared_ptr<Item> item_;
	std::shared_ptr<SpriteRenderer> renderer_;
};
