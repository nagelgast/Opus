#pragma once

#include <vector>

template <typename T>
void RemoveByValue(std::vector<T>& vector, const T& value)
{
	vector.erase(std::remove(vector.begin(), vector.end(), value), vector.end());
}
