#include <iostream>
#include <queue>
#include <chrono>
#include <locale>

double measure_queue_push(int n) {
    std::queue<int> q;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++) {
        q.push(i);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;
    return elapsed.count();
}

int main() {
    setlocale(LC_ALL, "Russian");

    int sizes[] = {
        10, 100, 1000, 5000, 10000,
        50000, 100000, 500000, 1000000,
        5000000, 10000000, 50000000, 100000000
    };

    std::cout << "N\t\tВремя (мс)" << std::endl;

    for (int i = 0; i < 13; i++) {
        double time_ms = measure_queue_push(sizes[i]);
        std::cout << sizes[i] << "\t\t" << time_ms << std::endl;
    }

    return 0;
}