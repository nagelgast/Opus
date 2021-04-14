#include "pch.h"
#include "SFMLWindow.h"

#include <string>
#include <SFML/Window/Event.hpp>

SFMLWindow::SFMLWindow(const int width, const int height, const int fps_limit, const std::string& title) :
	window_(std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), title))
{
	window_->setFramerateLimit(fps_limit);
}

bool SFMLWindow::IsOpen()
{
	return window_->isOpen();
}

void SFMLWindow::HandleEvents()
{
	sf::Event event{};
	while (window_->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window_->close();
		}
	}
}

sf::RenderWindow& SFMLWindow::GetWindow() const
{
	return *window_;
}
