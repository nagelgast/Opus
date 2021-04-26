#pragma once

#include "../Opus/Core.h"

class Loot :
    public Component
{
	void OnDestroy() override;
	void SpawnItem();
};

