#pragma once

#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>

#include "BaseWindow.h"

class SFMLWindow final : public BaseWindow
{
public:
	SFMLWindow(int width, int height, int fps_limit, const std::string& title);
	bool IsOpen() override;
	void HandleEvents() override;
	
	sf::RenderWindow& GetWindow() const;
private:
	std::unique_ptr<sf::RenderWindow> window_;
};

