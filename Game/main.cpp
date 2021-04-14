#include "../Opus/Camera.h"
#include "Enemy.h"
#include "../Opus/Game.h"
#include "Player.h"
#include "Wall.h"
#include "../Opus/ShapeRenderer.h"

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

		Entity main_camera {};
		auto camera = main_camera.AddComponent<Camera>();
		camera->SetTarget(player);
		game->renderer_->SetCamera(camera);
		game->entity_controller_.AddEntity(std::move(main_camera));

		const auto margin = 120;
		
		Entity health_globe {};
		health_globe.AddComponent(ShapeRenderer(Shape::kCircle, 1,0,0,1, false));
		health_globe.SetShape(Shape::kCircle);
		health_globe.SetPosition(margin, kScreenHeight-margin);
		health_globe.SetSize(100, 100);
		game->entity_controller_.AddEntity(std::move(health_globe));

		Entity mana_globe {};
		mana_globe.AddComponent(ShapeRenderer(Shape::kCircle, 0, 0, 1, 1, false));
		mana_globe.SetShape(Shape::kCircle);
		mana_globe.SetPosition(kScreenWidth-margin, kScreenHeight - margin);
		mana_globe.SetSize(100, 100);
		game->entity_controller_.AddEntity(std::move(mana_globe));


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
