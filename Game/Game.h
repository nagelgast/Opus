#pragma once

#include "BaseInputHandler.h"
#include "BaseRenderer.h"
#include "BaseTime.h"
#include "EntityController.h"

class Game
{
public:
	explicit Game(BaseRenderer& renderer, BaseInputHandler& input_handler, BaseTime& time);
	void Initialize();
	void Tick();
	void Exit();

private:
	void HandleInput() const;
	void FixedUpdate();
	void UpdateEntities();
	void HandleOutput();

	BaseRenderer& renderer_;
	BaseInputHandler& input_handler_;
	BaseTime& time_;
	EntityController entity_controller_;
};
