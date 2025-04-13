#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

bool isSorted(const std::vector<int>& vector) {
	return std::is_sorted(vector.begin(), vector.end());
}

int main()
{
	std::vector<int> vector = { 1, 2, 3, 5, 7, 98 };

	std::cout << isSorted(vector);
	std::cout << RAND_MAX;
}