#pragma once

class BaseWindow
{
public:
	virtual ~BaseWindow() = default;
	virtual bool IsOpen() = 0;
	virtual void HandleEvents() = 0;
};