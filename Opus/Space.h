#pragma once
#include "Entity.h"

class Space : public EntitySpawner, public EntityController
{
public:
	Space(): EntitySpawner(*this), EntityController(*this)
	{
	}
};
