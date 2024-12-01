#include <iostream>
#include <limits.h>
#include <cstdlib>
#include <ctime>

using namespace std;

// Функция для генерации матрицы стоимостей маршрутов
void generateCostMatrix(int** graph, int n, int maxCost) {
    srand(static_cast<unsigned int>(time(0)));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                graph[i][j] = 0;
            }
            else {
                graph[i][j] = rand() % maxCost + 1; // Случайная стоимость от 1 до maxCost
            }
        }
    }
}

// Функция для вывода матрицы
void printMatrix(int** graph, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << graph[i][j] << "\t";
        }
        cout << endl;
    }
}

// Функция для вычисления стоимости пути
int tsp(int** graph, int* path, int pos, int n, int count, int cost) {
    int answer = INT_MAX;
    if (count == n && graph[pos][0]) {
        return min(answer, cost + graph[pos][0]);
    }

    for (int i = 0; i < n; i++) {
        if (graph[pos][i] && !(path[i])) {
            path[i] = 1;
            answer = min(answer, tsp(graph, path, i, n, count + 1, cost + graph[pos][i]));
            path[i] = 0;
        }
    }
    return answer;
}

int main() {
    const int minCities = 2;
    const int maxCities = 10;
    const int maxCost = 100;

    for (int N = minCities; N <= maxCities; N++) {
        // Создание матрицы стоимостей
        int** graph = new int* [N];
        for (int i = 0; i < N; i++) {
            graph[i] = new int[N];
        }

        generateCostMatrix(graph, N, maxCost);

        cout << "The generated cost matrix for " << N << " cities:\n";
        printMatrix(graph, N);

        // Массив посещённых городов
        int* path = new int[N]();
        path[0] = 1;

        // Измеряем время выполнения
        clock_t start = clock();
        int answer = tsp(graph, path, 0, N, 1, 0); // Запускаем TSP
        clock_t end = clock();

        double timeTaken = double(end - start) / CLOCKS_PER_SEC;

        cout << "The minimum cost of the path: " << answer << endl;
        cout << "Time taken: " << timeTaken << " seconds\n\n";

        // Освобождение памяти
        delete[] path;
        for (int i = 0; i < N; i++) {
            delete[] graph[i];
        }
        delete[] graph;
    }

    return 0;
} 