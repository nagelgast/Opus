#include "pch.h"
#include "Camera.h"

#include "Transform.h"

void Camera::Update()
{
	if(target_)
	{
		entity_->GetTransform().SetPosition(target_->GetTransform().GetPosition() + offset_);
	}
}

void Camera::SetTarget(Entity& target)
{
	target_ = &target;
}
