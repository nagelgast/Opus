#include "Enemy.h"
#include "MouseHandler.h"
#include "Player.h"
#include "PlayerInventory.h"
#include "ScreenManager.h"
#include "Wall.h"
#include "PlayerController.h"

#include "../Opus/Core.h"
#include "../Opus/Camera.h"
#include "../Opus/ShapeRenderer.h"
#include "../Opus/Shape.h"

const int kScreenWidth = 1024;
const int kScreenHeight = 768;
const int kFpsLimit = 60;
const int kFixedTimeStepMs = 2;

int main()
{
	auto* game = new Game(kScreenWidth, kScreenHeight, kFpsLimit, kFixedTimeStepMs, "Game");


	// TODO Add naming to layers and force symmetry
	auto collision_matrix = std::map<int, std::vector<int>>();

	collision_matrix[0] = {0, 1, 2};
	collision_matrix[1] = {0, 1};
	collision_matrix[2] = {0, 2};

	game->SetCollisionMatrix(collision_matrix);

	// Load in starting entities
	{
		auto& root = game->GetRoot();

		auto player = root.Instantiate<Player>();
		player->SetName("Player");
		player->GetTransform().CenterOrigin();

		{
			auto main_camera = root.Instantiate();
			auto camera = main_camera->AddComponent(Camera());
			camera->SetTarget(player);
			game->SetCamera(camera);
		}

		const auto margin = 120;


		{
			auto health_globe = root.Instantiate({margin, kScreenHeight - margin});
			health_globe->AddComponent(ShapeRenderer(Shape::kCircle, {1, 0, 0}, false));
			health_globe->GetTransform().SetScale(100, 100);
		}

		{
			auto mana_globe = root.Instantiate({kScreenWidth - margin, kScreenHeight - margin});
			mana_globe->AddComponent(ShapeRenderer(Shape::kCircle, {0, 0, 1}, false));
			mana_globe->GetTransform().SetScale(100, 100);
		}

		auto screen_manager = root.Instantiate<ScreenManager>();

		auto mouse = root.Instantiate<MouseSlot>();
		mouse->AddComponent(MouseHandler(screen_manager, player->GetComponent<PlayerController>(), mouse));

		{
			auto player_inventory = root.Instantiate<PlayerInventory>();
			player_inventory->Initialize(mouse, screen_manager->player_inventory_screen_);
		}

		{
			const auto wall1 = root.Instantiate<Wall>({500, 500});
			wall1->SetName("Wall1");
			wall1->GetTransform().CenterOrigin();
		}
		{
			const auto wall2 = root.Instantiate<Wall>({300, 500});
			wall2->SetName("Wall2");
			wall2->GetTransform().CenterOrigin();
		}

		{
			const auto enemy = root.Instantiate<Enemy>({500, 100});
			enemy->SetName("Enemy");
			enemy->GetTransform().CenterOrigin();
		}
	}

	game->Run();

	game->Exit();

	return 0;
}
