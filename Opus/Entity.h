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

class Entity
{
public:
	Entity();
	virtual ~Entity();

	Entity(Entity&) = delete;
	Entity(Entity&&) = delete;
	Entity& operator=(Entity& other) = delete;
	Entity& operator=(Entity&& other) = delete;

	virtual void Awake()
	{
	}

	virtual void Start()
	{
	}

	virtual void Update()
	{
	}

	virtual void FixedUpdate()
	{
	}

	void Destroy();

	RectCollider& AddComponent(const RectCollider& c);
	CircleCollider& AddComponent(const CircleCollider& c);
	
	Entity& Instantiate() const;
	Entity& Instantiate(const Vector2& position) const;
	Entity& Instantiate(Transform& parent) const;

	template <typename T>
	T& Instantiate()
	{
		return ec_->CreateEntity<T>();
	}

	template <typename T>
	T& Instantiate(const Vector2& position)
	{
		auto& entity = ec_->CreateEntity<T>();
		entity.transform_->SetPosition(position);
		return entity;
	}

	template <typename T>
	T& Instantiate(Transform& parent)
	{
		auto& entity = ec_->CreateEntity<T>();
		entity.transform_->SetParent(parent);
		entity.transform_->SetLocalPosition({0, 0});
		return entity;
	}

	template <typename T>
	T& AddComponent(T c)
	{
		auto c_ptr = std::make_unique<T>(c);
		c_ptr->entity_ = this;

		const auto type = std::type_index(typeid(*c_ptr));
		components_[type] = std::move(c_ptr);

		components_[type]->Awake();

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
	const Input& GetInput() const;

	Transform& GetTransform() const;

	std::string GetName() const;
	void SetName(const std::string& name);
	void SetVisible(bool value);

	BaseEntityRenderer* CreateRenderer();
	bool ShouldRender() const;
	BaseEntityRenderer* GetRenderer() const;
	void RecalculateVisibility(Transform& parent);
	void RecalculateChildVisibility() const;
	bool HasRenderer() const;

	void OnCollision(const Collider& other);

private:
	void OnDestroy();
	void StartComponents();
	void UpdateComponents();
	void FixedUpdateComponents();

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
