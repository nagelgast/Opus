#include "TargetingSystem.h"

#include "../Opus/Input.h"

void TargetingSystem::Update()
{
	target_ = nullptr;
}

std::shared_ptr<Targetable> TargetingSystem::GetTarget()
{
	return target_;
}

void TargetingSystem::SetTarget(std::shared_ptr<Targetable> targetable)
{
	target_ = targetable;
}
