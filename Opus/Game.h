#pragma once

#include <memory>
#include <string>

#include "BaseInputHandler.h"
#include "BaseRenderer.h"
#include "BaseTime.h"
#include "EntityController.h"
#include "CollisionSystem.h"


#include "BaseWindow.h"

class Game
{
public:
	explicit Game(int width, int height, int fps_limit, int fixed_update_ms, const std::string& title);

	void Run();
	void Exit();

	Entity& GetRoot() const;
	void SetCamera(const Camera& camera) const;
	void SetCollisionMatrix(const std::map<int, std::vector<int>>& collision_matrix);
	
	static CollisionSystem& GetCollisionSystem();

private:
	void HandleInput() const;
	void FixedUpdate();
	void Update();
	void HandleOutput();

	std::unique_ptr<BaseWindow> window_;
	std::unique_ptr<BaseRenderer> renderer_;
	std::unique_ptr<BaseInputHandler> input_handler_;
	std::unique_ptr<BaseTime> time_;

	EntityController entity_controller_;
	Entity* root_ = nullptr;
};
