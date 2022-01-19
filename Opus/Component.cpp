#include "pch.h"
#include "Component.h"

#include "Transform.h"

Transform& Component::GetTransform() const
{
	return entity_->GetTransform();
}

Entity& Component::Create(const std::string& name) const
{
	return entity_->Instantiate(name);
}

Entity& Component::Create(const Vector2& position, const std::string& name) const
{
	return entity_->Instantiate(position, name);
}

Entity& Component::Create(Transform& parent, const std::string& name) const
{
	return entity_->Instantiate(parent, name);
}

Entity& Component::CreateHere(const std::string& name) const
{
	return entity_->Instantiate(GetTransformPosition(), name);
}

Entity& Component::CreateChild(const std::string& name) const
{
	return entity_->Instantiate(GetTransform(), name);
}

Vector2 Component::GetTransformPosition() const
{
	return GetTransform().GetPosition();
}
