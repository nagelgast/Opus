#include "pch.h"
#include "EntitySpawner.h"

#include "Entity.h"
#include "Space.h"
#include "Transform.h"

Entity& EntitySpawner::Create(const std::string& name) const
{
	auto& entity = space_->CreateEntity();
	entity.SetName(name);
	return entity;
}

Entity& EntitySpawner::Create(const Vector2& position, const std::string& name) const
{
	auto& entity = Create(name);
	entity.GetTransform().SetPosition(position);
	return entity;
}

Entity& EntitySpawner::Create(Transform& parent, const std::string& name) const
{
	auto& entity = Create(name);
	entity.GetTransform().SetParent(parent);
	entity.GetTransform().SetLocalPosition({ 0, 0 });
	return entity;
}
