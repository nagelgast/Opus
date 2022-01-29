#pragma once

#include <memory>
#include <vector>

class Space;
class BaseTime;
class BaseRenderer;
class Entity;
struct Input;

class EntityController
{
public:
	explicit EntityController(Space& space);

	void DestroyEntity(Entity& entity);
	Entity& CreateEntity();

	const std::vector<std::shared_ptr<Entity>>& GetEntities() const;
	void FixedUpdate() const;

	void Update();

private:
	std::vector<std::shared_ptr<Entity>> entities_;
	std::vector<std::shared_ptr<Entity>> new_entities_;

	Space& space_;
};
