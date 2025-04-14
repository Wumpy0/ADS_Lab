#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <fstream>

bool isSorted(const std::vector<int>& vector) {
	return std::is_sorted(vector.begin(), vector.end());
}

int getRandomNumber(int from, int to) {
	std::random_device randomDevice;
	std::mt19937 generator(randomDevice());
	std::uniform_int_distribution<int> bring(from, to);
	return bring(generator);
}

void generateFile(const std::string& filename, int size, int min, int max) {
	std::ofstream out(filename);
	for (int i = 0; i < size; ++i) {
		out << getRandomNumber(min, max) << " ";
	}

    std::cout << "Generated " << filename << " with " << size << " elements." << std::endl;
}

int main()
{
	std::vector<int> sizes = { 10000, 100000, 1000000 };
	std::vector<int> values = { 10, 1000, 100000 };

	for (int size : sizes) {
		for (int value : values) {
			std::string filename = std::to_string(size) + "_numbers_in_range_" + std::to_string(value) + ".txt";
			generateFile(filename, size, value * -1, value);
		}
	}
}