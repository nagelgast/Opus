#pragma once

#include "Entity.h"

class Collider;
class Transform;

class Component
{
public:
	Component() = default;
	Component(Component&&) noexcept;
	
	Component(const Component&) = default;
	Component& operator=(Component& other) = delete;
	Component& operator=(Component&& other) = delete;
	
	virtual ~Component() = default;
	virtual void Awake() {}
	virtual void Start() {}
	virtual void Update() {}
	virtual void FixedUpdate() {}
	virtual void OnCollision(const Collider& other) {}
	virtual void OnDestroy() {}

	Entity* entity_ = nullptr;

	template <typename T>
	T& AddComponent(T c)
	{
		return entity_->AddComponent<T>(c);
	}

	template <typename T>
	T* GetComponent()
	{
		return entity_->GetComponent<T>();
	}

	Transform& GetTransform() const;

	Entity& Create(const std::string& name = std::string()) const;
	Entity& Create(const Vector2& position, const std::string& name = std::string()) const;
	Entity& Create(Transform& parent, const std::string& name = std::string()) const;
	Entity& CreateHere(const std::string& name = std::string()) const;
	Entity& CreateChild(const std::string& name = std::string()) const;

	template <typename T>
	T& Create(const std::string& name = std::string()) const { return entity_->Instantiate<T>(name); }
	template <typename T>
	T& Create(const Vector2& position, const std::string& name = std::string()) const { return entity_->Instantiate<T>(position, name); }
	template <typename T = Entity>
	T& Create(Transform& parent, const std::string& name = std::string()) const { return entity_->Instantiate<T>(parent, name); }
	template <typename T = Entity>
	T& CreateHere(const std::string& name = std::string()) const { return entity_->Instantiate<T>(GetTransformPosition(), name); }
	template <typename T = Entity>
	T& CreateChild(const std::string& name = std::string()) const { return entity_->Instantiate<T>(GetTransform(), name); }
private:
	Vector2 GetTransformPosition() const;
};

inline Component::Component(Component&& c) noexcept : entity_(c.entity_)
{
}
