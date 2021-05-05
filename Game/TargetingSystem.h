#pragma once

#include "Targetable.h"
#include "../Opus/Core.h"
#include <memory>

class MouseItem;

class TargetingSystem :
    public Component
{
public:
	void SetMouseItem(const std::shared_ptr<MouseItem>& mouse_item);
	void Update() override;
	std::shared_ptr<Targetable> GetTarget();
	void SetTarget(std::shared_ptr<Targetable> targetable);
private:
	std::shared_ptr<Targetable> target_;
	std::shared_ptr<MouseItem> mouse_item_;
};
