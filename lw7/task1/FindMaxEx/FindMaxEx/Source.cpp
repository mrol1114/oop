#include "VectorUtils.h"

int main()
{
	int max;
	std::vector<int> arr = { 3, 4, 5 };

	FindMax(arr, max, [](int first, int second) { return first < second; });
}