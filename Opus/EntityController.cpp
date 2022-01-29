#include "pch.h"
#include "EntityController.h"

#include "Entity.h"
#include "Space.h"
#include "VectorExtensions.h"

EntityController::EntityController(Space& space): space_(space)
{
}

void EntityController::DestroyEntity(Entity& entity)
{
	// We probably have memory leaks?
	// Perf - Can probably be done in a single iterator
	const auto entity_iter = std::find_if(entities_.begin(), entities_.end(), 
	[&entity](std::shared_ptr<Entity> const& i)
	{
		return i.get() == &entity;
	});
	if(entity_iter == entities_.end()) return;
	const auto value = *entity_iter;

	RemoveByValue(entities_, value);
}

Entity& EntityController::CreateEntity()
{
	const auto entity = std::make_shared<Entity>();
	entity->space_ = &space_;
	new_entities_.push_back(entity);
	// TODO Fix stack memory warning
	return *entity;
}

// Should this call protect the entities somehow?
const std::vector<std::shared_ptr<Entity>>& EntityController::GetEntities() const
{
	return entities_;
}

void EntityController::FixedUpdate() const
{
	for (auto& entity : entities_)
	{
		entity->FixedUpdate();
	}
}

void EntityController::Update()
{
	const auto new_entities = new_entities_;
	new_entities_.clear();
	for (const auto& entity : new_entities)
	{
		entity->Start();
		entities_.push_back(entity);
	}

	std::vector<std::shared_ptr<Entity>> destroyed_entities;
	for (const auto& entity : entities_)
	{
		entity->Update();
		
		if (entity->destroyed_)
		{
			destroyed_entities.push_back(entity);
		}
	}

	for (const auto& entity : destroyed_entities)
	{
		DestroyEntity(*entity);
	}
}
