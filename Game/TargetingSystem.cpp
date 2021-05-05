#include "TargetingSystem.h"

void TargetingSystem::SetMouseItem(const std::shared_ptr<MouseItem>& mouse_item)
{
	mouse_item_ = mouse_item;
}

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
