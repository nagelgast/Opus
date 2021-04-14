#pragma once

#include <memory>
#include <vector>

class BaseTime;
class BaseRenderer;
class Entity;
struct Input;

class EntityController
{
public:
	explicit EntityController(const BaseRenderer& renderer, const BaseTime& time, const Input& input);
	void DestroyEntity(Entity& entity);
	std::shared_ptr<Entity> AddEntity(Entity&& e);
	std::vector<std::shared_ptr<Entity>>& GetEntities();

	const BaseRenderer& GetRenderer() const;
	const BaseTime& GetTime() const;
	const Input& GetInput() const;
	

private:
	std::vector<std::shared_ptr<Entity>> entities_;
	const BaseRenderer& renderer_;
	const BaseTime& time_;
	const Input& input_;
};
