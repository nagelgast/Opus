#include "Camera.h"

void Camera::Update()
{
	if(!target_.expired())
	{
		const auto target = target_.lock();
		entity_->SetPosition(target->GetPosition() + offset_);
	}
}

void Camera::SetTarget(const std::shared_ptr<Entity>& target)
{
	target_ = target;
}
