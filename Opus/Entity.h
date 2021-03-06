#pragma once

#include <memory>
#include <map>
#include <string>
#include <typeindex>
#include <vector>

#include "EntityController.h"

class CircleCollider;
class RectCollider;
class Collider;
class Transform;
class BaseEntityRenderer;
struct Vector2;
class Component;
struct Input;

class Entity final
{
public:
	Entity();
	~Entity();

	Entity(Entity&) = delete;
	Entity(Entity&&) = delete;
	Entity& operator=(Entity& other) = delete;
	Entity& operator=(Entity&& other) = delete;
	
	void Destroy();

	RectCollider& AddComponent(const RectCollider& c);
	CircleCollider& AddComponent(const CircleCollider& c);
	
	Entity& Instantiate(const std::string& name = std::string()) const;
	Entity& Instantiate(const Vector2& position, const std::string& name = std::string()) const;
	Entity& Instantiate(Transform& parent, const std::string& name = std::string()) const;

	template <typename T>
	T& Instantiate(const std::string& name = std::string())
	{
		auto& entity = Instantiate(name);
		T& component = entity.AddComponent<T>();
		return component;
	}

	template <typename T>
	T& Instantiate(const Vector2& position, const std::string& name = std::string())
	{
		auto& entity = Instantiate(position, name);
		auto& component = entity.AddComponent<T>();
		return component;
	}
	
	template <typename T>
	T& Instantiate(Transform& parent, const std::string& name = std::string())
	{
		auto& entity = Instantiate(parent, name);
		auto& component = entity.AddComponent<T>();

		return component;
	}

	template <typename T>
	T& AddComponent()
	{
		auto c_ptr = std::make_unique<T>();
		c_ptr->entity_ = this;

		const auto type = std::type_index(typeid(*c_ptr));
		components_[type] = std::move(c_ptr);

		AwakeComponent(type);

		return static_cast<T&>(*components_[type]);
	}

	template <typename T>
	T& AddComponent(T c)
	{
		auto c_ptr = std::make_unique<T>(c);
		c_ptr->entity_ = this;

		const auto type = std::type_index(typeid(*c_ptr));
		components_[type] = std::move(c_ptr);

		AwakeComponent(type);

		return static_cast<T&>(*components_[type]);
	}


	template <typename T>
	T* GetComponent()
	{
		const std::type_index index(typeid(T));

		if (components_.count(index) != 0)
		{
			return static_cast<T*>(components_[index].get());
		}

		return nullptr;
	}

	std::vector<std::shared_ptr<Entity>>& GetEntities() const;
	float GetDeltaTime() const;
	float GetFixedDeltaTime() const;

	Transform& GetTransform() const;

	std::string GetName() const;
	void SetName(const std::string& name);
	void SetVisible(bool value);

	BaseEntityRenderer* CreateRenderer();
	bool ShouldRender() const;
	BaseEntityRenderer* GetRenderer() const;
	void RecalculateVisibility(const Transform& parent);
	void RecalculateChildVisibility() const;
	bool HasRenderer() const;

	void OnCollision(const Collider& other) const;

private:
	void OnDestroy() const;
	void Start() const;
	void Update() const;
	void FixedUpdate() const;

	void AwakeComponent(std::type_index type);

	std::string name_;
	EntityController* ec_ = nullptr;
	Transform* transform_;
	std::unique_ptr<BaseEntityRenderer> renderer_;

	Collider* collider_ = nullptr;
	std::map<std::type_index, std::unique_ptr<Component>> components_{};

	bool visible_ = true;
	bool parent_visible_ = true;
	bool destroyed_ = false;

	friend class EntityController;
};
