#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <algorithm>
#include <locale>

int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void parallelQuickSort(std::vector<int>& arr, int low, int high, int numThreads) {
    if (low >= high)
        return;

    if (numThreads <= 1 || (high - low) < 1000) {
        quickSort(arr, low, high);
        return;
    }

    int pi = partition(arr, low, high);

    int leftThreads = numThreads / 2;
    int rightThreads = numThreads - leftThreads;

    std::thread leftThread(parallelQuickSort, std::ref(arr), low, pi - 1, leftThreads);
    parallelQuickSort(arr, pi + 1, high, rightThreads);
    leftThread.join();
}

double measureQS(std::vector<int> arr) {
    auto start = std::chrono::high_resolution_clock::now();
    quickSort(arr, 0, arr.size() - 1);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    return elapsed.count();
}

double measureParQS(std::vector<int> arr, int threads) {
    auto start = std::chrono::high_resolution_clock::now();
    parallelQuickSort(arr, 0, arr.size() - 1, threads);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    return elapsed.count();
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(0));

    int sizes[] = {100, 1000, 10000, 20000, 30000, 40000, 50000};

    std::cout << "N\t\tQS\t\tQS_2t\t\tQS_4t\t\tQS_8t" << std::endl;

    for (int k = 0; k < 7; k++) {
        int n = sizes[k];
        std::vector<int> base(n);
        for (int i = 0; i < n; i++)
            base[i] = rand() % 10000000;

        double t1 = measureQS(base);
        double t2 = measureParQS(base, 2);
        double t4 = measureParQS(base, 4);
        double t8 = measureParQS(base, 8);

        std::cout << n << "\t\t" << t1 << "\t\t" << t2 << "\t\t" << t4 << "\t\t" << t8 << std::endl;
    }

    return 0;
}
