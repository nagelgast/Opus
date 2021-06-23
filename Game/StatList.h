#pragma once
#include <memory>
#include <vector>

#include "Stat.h"

class StatList
{
public:
	StatList() = default;

	StatList(const StatList& other) = delete;
	StatList(StatList&& other) noexcept = default;
	StatList& operator=(const StatList& other) = delete;
	StatList& operator=(StatList&& other) noexcept = default;

	template <typename T>
	void Add(T stat)
	{
		stats_.push_back(std::make_unique<T>(stat));
	}

	std::string GenerateText() const;
private:
	std::vector<std::unique_ptr<Stat>> stats_;
};
