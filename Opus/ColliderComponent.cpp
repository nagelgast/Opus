#include "pch.h"
#include "ColliderComponent.h"

#include "Physics.h"

bool ColliderComponent::CheckCollision(const ColliderComponent& collider) const
{
	return Physics::CheckCircleCollision(entity_->GetTransform(), collider.entity_->GetTransform());
}
