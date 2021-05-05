#pragma once

#include "Entity.h"

class Collider;

class Component
{
public:
	Component() = default;
	Component(Component&&) noexcept;
	
	Component(const Component&) = default;
	Component& operator=(Component& other) = delete;
	Component& operator=(Component&& other) = delete;
	
	virtual ~Component() = default;
	virtual void Start() {}
	virtual void Update() {}
	virtual void FixedUpdate() {}
	virtual void OnCollision(const Collider& other) {}
	virtual void OnDestroy() {}
	Entity* entity_ = nullptr;
};

inline Component::Component(Component&& c) noexcept : entity_(c.entity_)
{
}
