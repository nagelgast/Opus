#include "pch.h"
#include "Component.h"

#include "Transform.h"

Transform& Component::GetTransform() const
{
	return entity_->GetTransform();
}

Entity& Component::CreateHere(const std::string& name) const
{
	return Create(GetTransformPosition(), name);
}

Entity& Component::CreateChild(const std::string& name) const
{
	return Create(GetTransform(), name);
}

Vector2 Component::GetTransformPosition() const
{
	return GetTransform().GetPosition();
}
