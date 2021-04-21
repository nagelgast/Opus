#pragma once

#include "Entity.h"

class Collider;

class OPUS_API Component
{
public:
	virtual ~Component() = default;
	virtual void Start() {}
	virtual void Update() {}
	virtual void FixedUpdate() {}
	virtual void OnCollision(const Collider& other) {}
	Entity* entity_ = nullptr;
};