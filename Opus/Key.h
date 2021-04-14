#pragma once

struct __declspec(dllexport) Key
{
	bool pressed = false;
	bool released = false;
	bool held = false;
};
