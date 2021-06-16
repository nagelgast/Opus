#include "pch.h"
#include "Game.h"

#include "Entity.h"
#include "SFMLInputHandler.h"
#include "SFMLRenderer.h"
#include "SFMLTime.h"
#include "SFMLWindow.h"

Game::Game(const int width, const int height, const int fps_limit, const int fixed_update_ms, const std::string& title) :
	window_(std::make_unique<SFMLWindow>(width, height, fps_limit, title)),
	renderer_(std::make_unique<SFMLRenderer>(*window_)),
	input_handler_(std::make_unique<SFMLInputHandler>(*window_)),
	time_(std::make_unique<SFMLTime>(fixed_update_ms)),
	entity_controller_(*renderer_, *time_, input_handler_->GetInput())
{
	root_ = &entity_controller_.CreateEntity();
	root_->SetName("Root");
	instance_ = this;
}

void Game::Run()
{
	while (window_->IsOpen())
	{
		window_->HandleEvents();

		HandleInput();

		time_->Tick();

		const auto fixed_ticks = time_->GetFixedTimeStepTicks();
		
		for (auto i = 0; i < fixed_ticks; i++)
		{
			FixedUpdate();
		}

		Update();
		HandleOutput();
	}
}

void Game::Exit()
{

}

Entity& Game::GetRoot() const
{
	return *root_;
}

void Game::SetCamera(const Camera& camera) const
{
	renderer_->SetCamera(camera);
}

void Game::SetCollisionMatrix(const std::map<int, std::vector<int>>& collision_matrix)
{
	GetCollisionSystem().SetCollisionMatrix(collision_matrix);
}

CollisionSystem& Game::GetCollisionSystem()
{
	return instance_->collision_system_;
}

void Game::HandleInput() const
{
	input_handler_->UpdateInput();
}

void Game::FixedUpdate()
{
	GetCollisionSystem().FixedUpdate();
	entity_controller_.FixedUpdate();
}

void Game::Update()
{
	entity_controller_.Update();
}

void Game::HandleOutput()
{
	renderer_->Render(entity_controller_.GetEntities());
}

Game* Game::instance_;