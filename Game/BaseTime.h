#pragma once

class BaseTime
{
public:
	virtual float GetDeltaTime() const = 0;
	virtual float GetTimeSinceStartup() const = 0;
	virtual int GetFixedTimeStepTicks() const = 0;
	virtual void Tick() = 0;
};