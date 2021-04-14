#pragma once

struct Input;

class __declspec(dllexport) BaseInputHandler
{
public:
	virtual ~BaseInputHandler() = default;
	virtual const Input& GetInput() = 0;
	virtual void UpdateInput() = 0;
};