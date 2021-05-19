#pragma once

#include "../Opus/Core.h"

class InventorySlot : public Entity
{
public:
	void Awake() override;
private:
	void HandleHoverEnter();
	void HandleHoverExit();

	std::shared_ptr<Entity> highlight_;
};
