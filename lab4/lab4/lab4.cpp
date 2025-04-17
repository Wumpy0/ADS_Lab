#include <iostream>
#include <algorithm>
#include <vector>

bool isSorted(const std::vector<int>& vector) {
	return std::is_sorted(vector.begin(), vector.end());
}

int main()
{
    std::cout << "Hello World!\n";
}