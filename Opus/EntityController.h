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
	Entity& CreateEntity();

	std::vector<std::shared_ptr<Entity>>& GetEntities();
	void FixedUpdate() const;

	void Update();

	const BaseRenderer& GetRenderer() const;
	const BaseTime& GetTime() const;
	const Input& GetInput() const;
private:
	void AddEntity(const std::shared_ptr<Entity>& entity);
	std::vector<std::shared_ptr<Entity>> entities_;
	std::vector<std::shared_ptr<Entity>> new_entities_;
	
	const BaseRenderer& renderer_;
	const BaseTime& time_;
	const Input& input_;
};
