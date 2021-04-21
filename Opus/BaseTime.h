#pragma once

class __declspec(dllexport) BaseTime
{
public:
	virtual ~BaseTime() = default;
	virtual float GetDeltaTime() const = 0;
	virtual float GetFixedDeltaTime() const = 0;
	virtual float GetTimeSinceStartup() const = 0;
	virtual int GetFixedTimeStepTicks() const = 0;
	virtual void Tick() = 0;
};