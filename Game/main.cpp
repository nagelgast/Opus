#include "Enemy.h"
#include "MouseHandler.h"
#include "Player.h"
#include "PlayerItemStorage.h"
#include "ScreenManager.h"
#include "PlayerController.h"

#include "../Opus/Core.h"
#include "../Opus/Camera.h"
#include "../Opus/ShapeRenderer.h"
#include "../Opus/Shape.h"
#include "../Opus/SpriteRenderer.h"
#include "../Opus/RectCollider.h"

const int kScreenWidth = 1024;
const int kScreenHeight = 768;
const int kFpsLimit = 60;
const int kFixedTimeStepMs = 2;

Player& InitPlayer(Entity& root)
{
	return root.Instantiate<Player>("Player");
}

void InitCamera(Entity& root, Player& player, Game& game)
{
	auto& camera = root.Instantiate<Camera>("Main Camera");
	camera.SetTarget(*player.entity_);
	game.SetCamera(camera);
}

void InitHUD(Entity& root)
{
	const auto margin = 120;
	{
		auto& health_globe = root.Instantiate(Vector2{ margin, kScreenHeight - margin }, "Health Globe");
		health_globe.AddComponent(ShapeRenderer(Shape::kCircle, { 1, 0, 0 }, false));
		health_globe.GetTransform().SetScale(100, 100);
	}

	{
		auto& mana_globe = root.Instantiate(Vector2{ kScreenWidth - margin, kScreenHeight - margin }, "Mana Globe");
		mana_globe.AddComponent(ShapeRenderer(Shape::kCircle, { 0, 0, 1 }, false));
		mana_globe.GetTransform().SetScale(100, 100);
	}
}

void InitUI(Entity& root, PlayerController& pc)
{
	auto& screen_manager = root.Instantiate<ScreenManager>("Screen Manager");
	
	auto& mouse = root.Instantiate<MouseSlot>("Mouse Slot");
	mouse.AddComponent(MouseHandler(screen_manager, pc, mouse));
	
	Game::GetService<PlayerItemStorage>()->Initialize(mouse, *screen_manager.player_inventory_screen_);
}

void InitEntities(Entity& root)
{
	{
		const Sprite sprite{ "Sprites/atlas.png", {16, 275, 431, 172} };
		const auto& background = root.Instantiate<SpriteRenderer>({ 431 * 2, 172 * 2 }, "Background");
		background.SetSprite(sprite);
		auto& bg_trans = background.GetTransform();
		bg_trans.SetScale(4, 4);
	}
	{
		auto& pond_collider = root.Instantiate({ 550, 450 }, "Pond Collider");
		pond_collider.AddComponent(RectCollider(0, false, true));
		pond_collider.GetTransform().SetScale(200, 128);
	}
	{
		root.Instantiate<Enemy>({ 500, 100 }, "Enemy");
	}
}

int main()
{
	auto* game = new Game(kScreenWidth, kScreenHeight, kFpsLimit, kFixedTimeStepMs, "Game");

	// TODO Add naming to layers and force symmetry
	auto collision_matrix = std::map<int, std::vector<int>>();

	collision_matrix[0] = {0, 1, 2};
	collision_matrix[1] = {0, 1};
	collision_matrix[2] = {0, 2};

	game->SetCollisionMatrix(collision_matrix);

	// Initialize services
	game->AddService<PlayerItemStorage>();


	// Load in starting entities
	auto& root = game->GetRoot();
	InitEntities(root);
	auto& player = InitPlayer(root);
	InitCamera(root, player, *game);
	InitHUD(root);
	InitUI(root, *player.GetComponent<PlayerController>());

	game->Run();

	game->Exit();

	return 0;
}
