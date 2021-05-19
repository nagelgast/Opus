
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

		{
			auto main_camera = root.Instantiate();
			auto camera = main_camera->AddComponent(Camera());
			camera->SetTarget(player);
			game->SetCamera(camera);
		}
		
		const auto margin = 120;

		
		{
			auto health_globe = root.Instantiate();
			health_globe->AddComponent(ShapeRenderer(Shape::kCircle, 1,0,0,1, false));
			health_globe->GetTransform().SetPosition({margin, kScreenHeight-margin});
			health_globe->GetTransform().SetSize(100, 100);
		}
		
		{
			auto mana_globe = root.Instantiate();
			mana_globe->AddComponent(ShapeRenderer(Shape::kCircle, 0, 0, 1, 1, false));
			mana_globe->GetTransform().SetPosition({kScreenWidth-margin, kScreenHeight - margin});
			mana_globe->GetTransform().SetSize(100, 100);
		}

		auto screen_manager = root.Instantiate<ScreenManager>();

		auto mouse = root.Instantiate<MouseItem>();
		mouse->AddComponent(MouseHandler(screen_manager, player->GetComponent<PlayerController>(), mouse));
		
		{
			auto inventory = root.Instantiate();
			auto player_inventory = inventory->AddComponent(PlayerInventory());
			player_inventory->mouse_item_ = mouse;
			player_inventory->screen_ = screen_manager->player_inventory_screen_;
			player_inventory->inventory_ = player_inventory->screen_->player_inventory_;
		}
		
		{
			const auto wall1 = root.Instantiate<Wall>();
			wall1->SetName("Wall1");
		}
		{
			const auto wall2 = root.Instantiate<Wall>();
			wall2->GetTransform().SetPosition({300, 500});
			wall2->SetName("Wall2");
		}

		{
			const auto enemy = root.Instantiate<Enemy>();
			enemy->GetTransform().SetPosition({500, 100});
			enemy->SetName("Enemy");
		}
	}

	game->Run();

	game->Exit();
	
	return 0;
}
