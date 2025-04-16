﻿#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <fstream>
#include <chrono>
#include <iomanip>

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

void shellSortKnuth(std::vector<int>& vector) {
    int vectorSize = vector.size();

    int gap = 1;
    while (gap < vectorSize / 3) {
        gap = 3 * gap + 1;
    }

    while (gap >= 1) {
        for (int i = gap; i < vectorSize; i++) {
            int temp = vector[i];
            int j;
            for (j = i; j >= gap && vector[j - gap] > temp; j -= gap) {
                vector[j] = vector[j - gap];
            }
            vector[j] = temp;
        }
        gap /= 3;
    }
}

void shellSortSedgewick(std::vector<int>& vector) {
    int n = vector.size();

    std::vector<int> gaps;
    int k = 0;
    while (true) {
        int gap;
        if (k & 1) {
            gap = 8 * (1 << k) - 6 * (1 << ((k + 1) / 2)) + 1;
        }
        else {
            gap = 9 * (1 << k) - 9 * (1 << (k / 2)) + 1;
        }
        if (gap >= n) break;
        gaps.push_back(gap);
        k++;
    }

    for (int s = gaps.size() - 1; s >= 0; s--) {
        int gap = gaps[s];
        for (int i = gap; i < n; i++) {
            int temp = vector[i];
            int j;
            for (j = i; j >= gap && vector[j - gap] > temp; j -= gap) {
                vector[j] = vector[j - gap];
            }
            vector[j] = temp;
        }
    }
}

int main() {
    std::vector<std::string> filenames = {
        "10000_numbers_in_range_10.txt",
        "10000_numbers_in_range_1000.txt",
        "10000_numbers_in_range_100000.txt",
        "100000_numbers_in_range_10.txt",
        "100000_numbers_in_range_1000.txt",
        "100000_numbers_in_range_100000.txt",
        "1000000_numbers_in_range_10.txt",
        "1000000_numbers_in_range_1000.txt",
        "1000000_numbers_in_range_100000.txt"
    };

    const int runs = 3;
    std::ofstream resultsFile("results.txt");
    resultsFile << "Filename, Algorithm, Average (s), Sorted Correctly\n";
    resultsFile << std::fixed << std::setprecision(6);

    for (const auto& filename : filenames) {
        std::cout << "Testing file: " << filename << std::endl;
        auto originalData = loadFile(filename);

        // shellSort
        std::vector<double> times;
        bool allCorrect = true;

        for (int i = 0; i < runs; ++i) {
            auto data = originalData;
            auto start = std::chrono::high_resolution_clock::now();
            shellSort(data);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> duration = end - start;
            times.push_back(duration.count());

            if (!isSorted(data)) {
                allCorrect = false;
            }
        }

        double average = (times[0] + times[1] + times[2]) / runs;
        resultsFile << filename << ", shellSort, " << average << ", " << (allCorrect ? "Yes" : "No") << "\n";

        // shellSortKnuth
        times.clear();
        allCorrect = true;

        for (int i = 0; i < runs; ++i) {
            auto data = originalData;
            auto start = std::chrono::high_resolution_clock::now();
            shellSortKnuth(data);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> duration = end - start;
            times.push_back(duration.count());

            if (!isSorted(data)) {
                allCorrect = false;
            }
        }

        average = (times[0] + times[1] + times[2]) / runs;
        resultsFile << filename << ", shellSortKnuth, " << average << ", " << (allCorrect ? "Yes" : "No") << "\n";

        // shellSortSedgewick
        times.clear();
        allCorrect = true;

        for (int i = 0; i < runs; ++i) {
            auto data = originalData;
            auto start = std::chrono::high_resolution_clock::now();
            shellSortSedgewick(data);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> duration = end - start;
            times.push_back(duration.count());

            if (!isSorted(data)) {
                allCorrect = false;
            }
        }

        average = (times[0] + times[1] + times[2]) / runs;
        resultsFile << filename << ", shellSortSedgewick, " << average << ", " << (allCorrect ? "Yes" : "No") << "\n";
    }

    resultsFile.close();
    std::cout << "All tests completed!" << std::endl;

    return 0;
}