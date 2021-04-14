#pragma once

class __declspec(dllexport) BaseWindow
{
public:
	virtual ~BaseWindow() = default;
	virtual bool IsOpen() = 0;
	virtual void HandleEvents() = 0;
};