#pragma once

#include "Targetable.h"
#include "../Opus/Core.h"

class TargetingSystem :
    public Component
{
public:
	void Update() override;
	std::shared_ptr<Targetable> GetTarget();
	void SetTarget(std::shared_ptr<Targetable> targetable);
private:
	std::shared_ptr<Targetable> target_;
};
