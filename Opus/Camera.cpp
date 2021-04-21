#include "pch.h"
#include "Camera.h"

#include "Transform.h"

void Camera::Update()
{
	if(!target_.expired())
	{
		const auto target = target_.lock();
		entity_->GetTransform().SetPosition(target->GetTransform().GetPosition() + offset_);
	}
}

void Camera::SetTarget(const std::shared_ptr<Entity>& target)
{
	target_ = target;
}
