#include "../Opus/Camera.h"
#include "Enemy.h"
#include "../Opus/Game.h"
#include "Player.h"
#include "Wall.h"
#include "../Opus/ShapeRenderer.h"
#include "../Opus/Transform.h"
#include "../Opus/Shape.h"

const int kScreenWidth = 1024;
const int kScreenHeight = 768;
const int kFpsLimit = 60;
const int kFixedTimeStepMs = 2;

int main()
{
	auto* game = new Game(kScreenWidth, kScreenHeight, kFpsLimit, kFixedTimeStepMs, "Game");

	// Load in starting entities
	{
		const auto root = game->GetRoot();
		const auto player = root.AddEntity(Player());

		Entity main_camera {};
		auto camera = main_camera.AddComponent<Camera>();
		camera->SetTarget(player);
		game->SetCamera(camera);
		root.AddEntity(std::move(main_camera));

		const auto margin = 120;
		
		Entity health_globe {};
		health_globe.AddComponent(ShapeRenderer(Shape::kCircle, 1,0,0,1, false));
		health_globe.GetTransform().SetPosition(margin, kScreenHeight-margin);
		health_globe.GetTransform().SetSize(100, 100);
		root.AddEntity(std::move(health_globe));

		Entity mana_globe {};
		mana_globe.AddComponent(ShapeRenderer(Shape::kCircle, 0, 0, 1, 1, false));
		mana_globe.GetTransform().SetPosition(kScreenWidth-margin, kScreenHeight - margin);
		mana_globe.GetTransform().SetSize(100, 100);
		root.AddEntity(std::move(mana_globe));


		root.AddEntity(Wall());
		const auto wall = root.AddEntity(Wall());
		wall->GetTransform().SetPosition(300, 500);

		const auto enemy = root.AddEntity(Enemy());
		enemy->GetTransform().SetPosition(500, 100);
	}

	game->Run();

	game->Exit();
	
	return 0;
}
