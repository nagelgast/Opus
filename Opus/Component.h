#pragma once

#include "Entity.h"

class Collider;

class Component
{
public:
	virtual ~Component() = default;
	virtual void Start() {}
	virtual void Update() {}
	virtual void FixedUpdate() {}
	virtual void OnCollision(const Collider& other) {}
	virtual void OnDestroy() {}
	Entity* entity_ = nullptr;
};