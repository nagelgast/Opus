#pragma once

#include "BaseInputHandler.h"
#include "Input.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <initializer_list>

#include "../Opus/SFMLWindow.h"

struct Key;

class SFMLInputHandler final : public BaseInputHandler
{
public:
	explicit SFMLInputHandler(std::shared_ptr<BaseWindow> window);
	const Input& GetInput() override;
	void UpdateInput() override;

private:
	static void UpdateKeyboardKey(Key& key, std::initializer_list<sf::Keyboard::Key> key_aliases);
	static void UpdateKey(Key& key, bool held);
	
	const sf::RenderWindow& window_;
	Input input_;
};

