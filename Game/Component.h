#pragma once

#include "Entity.h"

class Component
{
public:
	virtual void Start() {}
	virtual void Update() {}
	Entity* entity_ = nullptr;
};