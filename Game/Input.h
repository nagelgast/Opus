#pragma once

#include "Key.h"
#include "Vector2.h"

struct __declspec(dllexport) Input
{
	Key up;
	Key down;
	Key left;
	Key right;
	
	Key action;
	Key move;
	Key run;

	Vector2 mouse_screen_pos;
	Vector2 mouse_world_pos;
};

