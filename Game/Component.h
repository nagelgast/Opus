#pragma once

#include "Entity.h"

class __declspec(dllexport) Component
{
public:
	virtual void Start() {}
	virtual void Update() {}
	Entity* entity_ = nullptr;
};