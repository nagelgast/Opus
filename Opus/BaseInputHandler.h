#pragma once

struct Input;

class BaseInputHandler
{
public:
	virtual ~BaseInputHandler() = default;
	virtual const Input& GetInput() = 0;
	virtual void UpdateInput() = 0;
};