#pragma once

#include <memory>
#include <string>

#include "BaseInputHandler.h"
#include "BaseRenderer.h"
#include "BaseTime.h"
#include "EntityController.h"

#include "BaseWindow.h"
#include "Opus.h"

class Game
{
public:
	OPUS_API explicit Game(int width, int height, int fps_limit, int fixed_update_ms, const std::string& title);

	OPUS_API void Run();
	OPUS_API void Exit();

	OPUS_API Entity& GetRoot() const;
	OPUS_API void SetCamera(const std::shared_ptr<Camera>& camera) const;
private:
	void HandleInput() const;
	void FixedUpdate();
	void Update();
	void HandleOutput();

	std::shared_ptr<BaseWindow> window_;
	std::unique_ptr<BaseRenderer> renderer_;
	std::unique_ptr<BaseInputHandler> input_handler_;
	std::unique_ptr<BaseTime> time_;


	EntityController entity_controller_;
	std::shared_ptr<Entity> root_;
};
