#pragma once

#include "Key.h"
#include "Vector2.h"

struct Input
{
	Key up;
	Key down;
	Key left;
	Key right;
	
	Key left_mouse;
	Key right_mouse;
	Key run;

	Key inventory;
	Key close_all_ui;

	Vector2 mouse_screen_pos;
	Vector2 mouse_world_pos;
};

