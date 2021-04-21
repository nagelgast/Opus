#pragma once

#include "Entity.h"

class OPUS_API Component
{
public:
	virtual ~Component() = default;
	virtual void Start() {}
	virtual void Update() {}
	Entity* entity_ = nullptr;
};