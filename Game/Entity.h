#pragma once

#include "Shape.h"
#include "BaseEntityRenderer.h"

#include <memory>
#include <map>
#include <typeindex>
#include <vector>

#include "../Opus/Opus.h"

namespace sf
{
	class Transformable;
}

class Vector2;
class EntityController;
class Component;
struct Input;

class Entity
{
public:
	OPUS_API Entity();
	OPUS_API Entity(Entity&);
	OPUS_API ~Entity();

	OPUS_API void Start(EntityController* ec);

	OPUS_API void Update();
	OPUS_API void Destroy();

	template <typename T> std::shared_ptr<T> AddComponent(T c)
	{
		auto c_ptr = std::make_shared<T>(c);
		c_ptr->entity_ = this;
		components_[std::type_index(typeid(*c_ptr))] = c_ptr;

		return c_ptr;
	}

	template <typename T> std::shared_ptr<T> GetComponent()
	{
		const std::type_index index(typeid(T));

		if (components_.count(index) != 0)
		{
			return std::static_pointer_cast<T>(components_[index]);
		}

		return nullptr;
	}

	OPUS_API std::shared_ptr<Entity> AddEntity(Entity&& e) const;
	OPUS_API std::vector<std::shared_ptr<Entity>>& GetEntities() const;
	OPUS_API float GetDeltaTime() const;
	OPUS_API const Input& GetInput() const;


	// TODO Handle with transform component
	OPUS_API void SetSize(float width, float height);
	OPUS_API Vector2 GetPosition() const;
	OPUS_API void SetPosition(float x, float y);
	OPUS_API void SetPosition(Vector2 position);
	OPUS_API void Move(Vector2 offset) const;
	OPUS_API Vector2 GetOrigin() const;
	OPUS_API Vector2 GetScale() const;

	// TODO Handle with collider component
	OPUS_API void SetShape(Shape shape);
	int layer_ = 0;
	Shape shape_ = Shape::kCircle;

	OPUS_API BaseEntityRenderer* CreateRenderer();
	OPUS_API BaseEntityRenderer* GetRenderer() const;
	OPUS_API bool HasRenderer() const;

private:
	EntityController* ec_ = nullptr;
	sf::Transformable* transformable_{};
	std::unique_ptr<BaseEntityRenderer> renderer_{};
	std::map<std::type_index, std::shared_ptr<Component>> components_{};
};
