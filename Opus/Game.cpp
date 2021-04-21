#include "pch.h"
#include "Game.h"

#include "Entity.h"
#include "SFMLInputHandler.h"
#include "SFMLRenderer.h"
#include "SFMLTime.h"
#include "SFMLWindow.h"

Game::Game(const int width, const int height, const int fps_limit, const int fixed_update_ms, const std::string& title) :
	window_(std::make_shared<SFMLWindow>(width, height, fps_limit, title)),
	renderer_(std::make_unique<SFMLRenderer>(window_)),
	input_handler_(std::make_unique<SFMLInputHandler>(window_)),
	time_(std::make_unique<SFMLTime>(fixed_update_ms)),
	entity_controller_(*renderer_, *time_, input_handler_->GetInput())
{
	root_ = entity_controller_.CreateEntity();
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

Entity& Game::GetRoot()
{
	return *root_;
}

void Game::HandleInput() const
{
	input_handler_->UpdateInput();
}

void Game::FixedUpdate()
{
	entity_controller_.collision_system_.FixedUpdate();
	auto entities = entity_controller_.GetEntities();
	for (const auto& entity : entities)
	{
		entity->FixedUpdate();
	}
}

void Game::Update()
{
	auto entities = entity_controller_.GetEntities();
	for (const auto& entity : entities)
	{
		entity->Update();
	}
}

void Game::HandleOutput()
{
	renderer_->Render(entity_controller_.GetEntities());
}
