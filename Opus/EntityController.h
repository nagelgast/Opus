#pragma once

#include <memory>
#include <vector>

#include "CollisionSystem.h"

class BaseTime;
class BaseRenderer;
class Entity;
struct Input;

class EntityController
{
public:
	explicit EntityController(const BaseRenderer& renderer, const BaseTime& time, const Input& input);
	void DestroyEntity(Entity& entity);
	std::shared_ptr<Entity> CreateEntity();

	template <typename T>
	std::shared_ptr<Entity> CreateEntity()
	{
		return AddEntity(std::make_shared<T>());
	}

	std::vector<std::shared_ptr<Entity>>& GetEntities();
	void FixedUpdate();

	void Update();

	const BaseRenderer& GetRenderer() const;
	const BaseTime& GetTime() const;
	const Input& GetInput() const;

	// Should be owned by Game
	CollisionSystem collision_system_;
private:
	std::shared_ptr<Entity> AddEntity(std::shared_ptr<Entity> entity);
	std::vector<std::shared_ptr<Entity>> entities_;
	std::vector<std::shared_ptr<Entity>> new_entities_;
	
	const BaseRenderer& renderer_;
	const BaseTime& time_;
	const Input& input_;
};
