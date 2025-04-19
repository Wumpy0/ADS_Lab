#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <chrono>
#include <iomanip>

bool isSorted(const std::vector<int>& vector) {
    return std::is_sorted(vector.begin(), vector.end());
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

void quickSort(std::vector<int>& vector) {

}

int main()
{
    std::vector<int> vector = loadFile("10000_numbers_in_range_10.txt");
    quickSort(vector);
    std::cout << isSorted(vector);
}