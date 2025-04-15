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

std::vector<int> loadFile(const std::string& filename) {
    std::ifstream in(filename);
    std::vector<int> vector;
    int number;
    while (in >> number) {
        vector.push_back(number);
    }
    return vector;
}

void shellSort(std::vector<int>& vector) {
    int vectorSize = vector.size();

    for (int gap = vectorSize / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < vectorSize; i++) {
            int temp = vector[i];
            int j;
            for (j = i; j >= gap && vector[j - gap] > temp; j -= gap) {
                vector[j] = vector[j - gap];
            }
            vector[j] = temp;
        }
    }
}

int main()
{
    std::vector<int> vector = loadFile("1000000_numbers_in_range_100000.txt");
    shellSort(vector);
    //for (int n : vector) {
    //    std::cout << n << " ";
    //}
    std::cout << std::endl << isSorted(vector);
}