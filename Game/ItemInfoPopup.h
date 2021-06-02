#pragma once

#include "../Opus/Core.h"

struct Item;

class ItemInfoPopup : public Entity
{
public:
	void Awake() override;
	void SetItem(const Item& item);
};

