#pragma once

#include <vector>

template <typename T>
void RemoveByValue(std::vector<T>& vector, const T& value)
{
	vector.erase(std::remove(vector.begin(), vector.end(), value), vector.end());
}

template <typename T>
bool Contains(std::vector<T>& vector, const T& value)
{
	return std::find(vector.begin(), vector.end(), value) != vector.end();
}