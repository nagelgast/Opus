#include "pch.h"
#include "EntityController.h"

#include "BaseTime.h"
#include "Entity.h"

EntityController::EntityController(const BaseRenderer& renderer, const BaseTime& time, const Input& input) : renderer_(renderer), time_(time), input_(input)
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
	entities_.erase(std::remove(entities_.begin(), entities_.end(), value), entities_.end());
}

std::shared_ptr<Entity> EntityController::CreateEntity()
{
	auto entity = std::make_shared<Entity>();
	AddEntity(entity);
	return entity;
}

// Should this call protect the entities somehow?
std::vector<std::shared_ptr<Entity>>& EntityController::GetEntities()
{
	return entities_;
}

void EntityController::FixedUpdate()
{
	collision_system_.FixedUpdate();
	auto entities = GetEntities();
	for (const auto& entity : entities)
	{
		entity->FixedUpdate();
		entity->FixedUpdateComponents();
	}
}

void EntityController::Update()
{
	auto new_entities = new_entities_;
	new_entities_.clear();
	for (const auto& entity : new_entities)
	{
		entity->Start();
		entity->StartComponents();
		entities_.push_back(entity);
	}

	std::vector<std::shared_ptr<Entity>> destroyed_entities;
	for (const auto& entity : entities_)
	{
		entity->Update();
		entity->UpdateComponents();
		
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

const BaseRenderer& EntityController::GetRenderer() const
{
	return renderer_;
}

const BaseTime& EntityController::GetTime() const
{
	return time_;
}

const Input& EntityController::GetInput() const
{
	return input_;
}

void EntityController::AddEntity(const std::shared_ptr<Entity>& entity)
{
	entity->ec_ = this;
	new_entities_.push_back(entity);
	entity->Awake();
}
