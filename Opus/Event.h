#pragma once

#include <functional>
#include <vector>

class Event
{
public:
	void operator()()
	{
		for (const auto& listener : listeners_)
		{
			listener();
		}
	}

	void operator+=(const std::function<void()>& listener)
	{
		listeners_.push_back(listener);
	}

private:
	std::vector<std::function<void()>> listeners_;
};

template <typename T>
class BaseEvent
{
public:
	void operator()(T args)
	{
		for (auto listener : listeners_)
		{
			listener(args);
		}
	}

	void operator+=(std::function<void(T)> listener)
	{
		listeners_.push_back(listener);
	}

private:
	std::vector<std::function<void(T)>&> listeners_;
};
