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
	return AddEntity(Entity());
}

std::shared_ptr<Entity> EntityController::AddEntity(Entity&& e)
{
	auto entity = std::make_shared<Entity>(e);
	entities_.push_back(entity);
	entity->Start(this);
	return entity;
}

// Should this call protect the entities somehow?
std::vector<std::shared_ptr<Entity>>& EntityController::GetEntities()
{
	return entities_;
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
