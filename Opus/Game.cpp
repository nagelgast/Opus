#include "pch.h"
#include "Game.h"

#include "Entity.h"
#include "SFMLInputHandler.h"
#include "SFMLRenderer.h"
#include "SFMLTextureManager.h"
#include "SFMLTime.h"
#include "SFMLWindow.h"

Game::Game(const int width, const int height, const int fps_limit, const int fixed_update_ms, const std::string& title) :
	window_(std::make_unique<SFMLWindow>(width, height, fps_limit, title)),
	renderer_(std::make_unique<SFMLRenderer>(*window_)),
	input_handler_(std::make_unique<SFMLInputHandler>(*window_)),
	time_(std::make_unique<SFMLTime>(fixed_update_ms)),
	texture_manager_(std::make_unique<SFMLTextureManager>())
{
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

Space& Game::GetWorldSpace()
{
	return instance_->world_space_;
}

Space& Game::GetScreenSpace()
{
	return instance_->screen_space_;
}

Space& Game::GetDebugSpace()
{
	return instance_->debug_space_;
}

void Game::SetCamera(const Camera& camera) const
{
	renderer_->SetCamera(camera);
}

void Game::SetCollisionMatrix(const std::map<int, std::vector<int>>& collision_matrix)
{
	GetCollisionSystem().SetCollisionMatrix(collision_matrix);
}

const BaseRenderer& Game::GetRenderer()
{
	return *instance_->renderer_;
}

const BaseTime& Game::GetTime()
{
	return *instance_->time_;
}

const Input& Game::GetInput()
{
	return instance_->input_handler_->GetInput();
}

CollisionSystem& Game::GetCollisionSystem()
{
	return instance_->collision_system_;
}

TextureManager& Game::GetTextureManager()
{
	return *instance_->texture_manager_;
}

void Game::HandleInput() const
{
	input_handler_->UpdateInput();
}

void Game::FixedUpdate()
{
	GetCollisionSystem().FixedUpdate();
	world_space_.FixedUpdate();
}

void Game::Update()
{
	world_space_.Update();
	screen_space_.Update();
	debug_space_.Update();
}

void Game::HandleOutput()
{
	renderer_->CheckDebugState(input_handler_->GetInput());
	renderer_->Render();
}

Game* Game::instance_;