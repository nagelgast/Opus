#include "SFMLInputHandler.h"

#include "Key.h"
#include <SFML/Window/Mouse.hpp>

SFMLInputHandler::SFMLInputHandler(sf::RenderWindow& window) : window_(window)
{
}

const Input& SFMLInputHandler::GetInput()
{
	return input_;
}

void SFMLInputHandler::UpdateInput()
{
	if(!window_.hasFocus()) return;
	
	UpdateKeyboardKey(input_.up, { sf::Keyboard::Up, sf::Keyboard::W });
	UpdateKeyboardKey(input_.down, { sf::Keyboard::Down, sf::Keyboard::S });
	UpdateKeyboardKey(input_.left, { sf::Keyboard::Left, sf::Keyboard::A });
	UpdateKeyboardKey(input_.right, { sf::Keyboard::Right, sf::Keyboard::D });
	UpdateKeyboardKey(input_.run, { sf::Keyboard::LShift});

	UpdateKey(input_.move, sf::Mouse::isButtonPressed(sf::Mouse::Left));
	UpdateKey(input_.action, sf::Mouse::isButtonPressed(sf::Mouse::Right));
	input_.mouse_screen_pos = Vector2(sf::Mouse::getPosition(window_));
	input_.mouse_world_pos = window_.mapPixelToCoords(sf::Vector2i(input_.mouse_screen_pos.x, input_.mouse_screen_pos.y));
}

void SFMLInputHandler::UpdateKeyboardKey(Key& key, std::initializer_list<sf::Keyboard::Key> key_aliases)
{
	auto held = false;
	for (auto key_alias : key_aliases)
	{
		if(sf::Keyboard::isKeyPressed(key_alias))
		{
			held = true;
			break;
		}
	}

	UpdateKey(key, held);
}

void SFMLInputHandler::UpdateKey(Key& key, const bool held)
{
	key.pressed = !key.held && held;
	key.released = key.held && !held;
	key.held = held;
}