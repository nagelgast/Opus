#include <SFML/Graphics.hpp>

#include "Game.h"
#include "SFMLRenderer.h"
#include "SFMLInputHandler.h"
#include "SFMLTime.h"

const int kScreenWidth = 1024;
const int kScreenHeight = 768;
const int kFpsLimit = 60;
const int kFixedTimeStepMs = 2;

int main()
{
	auto* window = new sf::RenderWindow(sf::VideoMode(kScreenWidth, kScreenHeight), "Game");
	window->setFramerateLimit(kFpsLimit);

	auto* renderer = new SFMLRenderer(*window);
	auto* input_handler = new SFMLInputHandler(*window);
	auto* time = new SFMLTime(kFixedTimeStepMs);

	auto* game = new Game(*renderer, *input_handler, *time);
	game->Initialize();

	while (window->isOpen())
	{
		sf::Event event{};
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window->close();
			}
		}

		game->Tick();
	}

	game->Exit();

	return 0;
}
