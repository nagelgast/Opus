#pragma once

#include "../Opus/Core.h"

class ItemData;

class Loot :
    public Component
{
	void Awake() override;
	void OnDestroy() override;
	void SpawnItem() const;
private:
	ItemData* item_data_;
};
