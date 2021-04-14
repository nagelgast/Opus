#pragma once

#include "Shape.h"
#include "BaseEntityRenderer.h"

#include <memory>
#include <map>
#include <typeindex>
#include <vector>

namespace sf
{
	class Transformable;
}

class Vector2;
class EntityController;
class Component;
struct Input;

class __declspec(dllexport) Entity
{
public:
	Entity();
	Entity(Entity&);
	~Entity();

	void Start(EntityController* ec);

	void Update();
	void Destroy();

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

	std::shared_ptr<Entity> AddEntity(Entity&& e) const;
	std::vector<std::shared_ptr<Entity>>& GetEntities() const;
	float GetDeltaTime() const;
	const Input& GetInput() const;


	// TODO Handle with transform component
	void SetSize(float width, float height);
	Vector2 GetPosition() const;
	void SetPosition(float x, float y);
	void SetPosition(Vector2 position);
	void Move(Vector2 offset) const;
	Vector2 GetOrigin() const;
	Vector2 GetScale() const;

	// TODO Handle with collider component
	void SetShape(Shape shape);
	int layer_ = 0;
	Shape shape_ = Shape::kCircle;

	BaseEntityRenderer* CreateRenderer();
	BaseEntityRenderer* GetRenderer() const;
	bool HasRenderer() const;

private:
	EntityController* ec_ = nullptr;
	sf::Transformable* transformable_{};
	std::unique_ptr<BaseEntityRenderer> renderer_{};
	std::map<std::type_index, std::shared_ptr<Component>> components_{};
};
