#include "pch.h"
#include "SFMLInputHandler.h"

#include "Key.h"
#include <SFML/Window/Mouse.hpp>

SFMLInputHandler::SFMLInputHandler(const std::shared_ptr<BaseWindow> window) :
	window_(static_cast<SFMLWindow&>(*window).GetWindow())
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

	UpdateKeyboardKey(input_.inventory, { sf::Keyboard::I});
	UpdateKeyboardKey(input_.close_all_ui, { sf::Keyboard::Space });

	UpdateKey(input_.left_mouse, sf::Mouse::isButtonPressed(sf::Mouse::Left));
	UpdateKey(input_.right_mouse, sf::Mouse::isButtonPressed(sf::Mouse::Right));

	const auto mouse_screen_pos = sf::Mouse::getPosition(window_);
	const auto mouse_world_pos = window_.mapPixelToCoords(mouse_screen_pos);
	input_.mouse_screen_pos = {static_cast<float>(mouse_screen_pos.x), static_cast<float>(mouse_screen_pos.y)};
	input_.mouse_world_pos = {static_cast<float>(mouse_world_pos.x), static_cast<float>(mouse_world_pos.y)};
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