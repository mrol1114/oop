#pragma once

#include <vector>

template <typename T>
bool DefaultLess(const T& first, const T& second)
{
	return first < second;
}

template <typename T, typename Less>
bool FindMax(std::vector<T> const& arr, T& maxValue, Less const& less = DefaultLess)
{
	if (arr.size() == 0)
	{
		return false;
	}

	T currMax = arr[0];
	for (T const& currValue: arr)
	{
		if (less(currMax, currValue))
		{
			currMax = currValue;
		}
	}

	std::swap(maxValue, currMax);
	return true;
}