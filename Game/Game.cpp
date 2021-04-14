#include "Game.h"

#include "Enemy.h"
#include "Player.h"
#include "Wall.h"


Game::Game(BaseRenderer& renderer, BaseInputHandler& input_handler, BaseTime& time) : renderer_(renderer), input_handler_(input_handler), time_(time), entity_controller_(renderer, time, input_handler_.GetInput())
{
}

void Game::Initialize()
{
	auto player = entity_controller_.AddEntity(Player());
	entity_controller_.AddEntity(Wall());
	auto wall = entity_controller_.AddEntity(Wall());
	wall->SetPosition(300, 500);

	auto enemy = entity_controller_.AddEntity(Enemy());
	enemy->SetPosition(500, 100);
}

void Game::Tick()
{
	HandleInput();

	time_.Tick();

	for (auto i = 0; i < time_.GetFixedTimeStepTicks(); i++)
	{
		FixedUpdate();
	}

	UpdateEntities();
	HandleOutput();
}

void Game::Exit()
{

}

void Game::HandleInput() const
{
	input_handler_.UpdateInput();
}

void Game::FixedUpdate()
{
	// Nothing implemented to use this yet
}

void Game::UpdateEntities()
{
	auto entities = entity_controller_.GetEntities();
	for (const auto& entity : entities)
	{
		entity->Update();
	}
}

void Game::HandleOutput()
{
	renderer_.Render(entity_controller_.GetEntities());
}
