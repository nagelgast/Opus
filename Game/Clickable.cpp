#include "Clickable.h"

#include <iostream>


#include "../Opus/Input.h"


void Clickable::Update()
{
	const auto& input = Game::GetInput();
	if(input.left_mouse.released)
	{
		const auto mouse_pos = input.mouse_world_pos;
		const auto pos = entity_->GetTransform().GetPosition();

		const auto max_distance = 5;
		
		if(abs(mouse_pos.x - pos.x) < max_distance && abs(mouse_pos.y - pos.y) < max_distance)
		{
			OnClick();
		}
	}
}

void Clickable::OnClick()
{
	std::cout << "Test";
}
