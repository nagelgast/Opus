#include "Camera.h"
#include "Enemy.h"
#include "Game.h"
#include "Player.h"
#include "Wall.h"

const int kScreenWidth = 1024;
const int kScreenHeight = 768;
const int kFpsLimit = 60;
const int kFixedTimeStepMs = 2;

int main()
{
	auto* game = new Game(kScreenWidth, kScreenHeight, kFpsLimit, kFixedTimeStepMs, "Game");

	// Load in starting entities
	{
		const auto player = game->entity_controller_.AddEntity(Player());

		auto main_camera = game->entity_controller_.AddEntity(Entity());
		auto camera = main_camera->AddComponent(Camera());
		camera->SetTarget(player);
		game->renderer_->SetCamera(camera);

		game->entity_controller_.AddEntity(Wall());
		auto wall = game->entity_controller_.AddEntity(Wall());
		wall->SetPosition(300, 500);

		auto enemy = game->entity_controller_.AddEntity(Enemy());
		enemy->SetPosition(500, 100);
	}

	game->Run();

	game->Exit();
	
	return 0;
}
