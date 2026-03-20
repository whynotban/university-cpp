#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <locale>
#include <algorithm>

void combSort(std::vector<int>& arr) {
    int n = arr.size();
    int gap = n - 1;
    while (gap > 1) {
        gap = (int)(gap / 1.3);
        int i = 0;
        while (i + gap < n) {
            if (arr[i] > arr[i + gap])
                std::swap(arr[i], arr[i + gap]);
            i++;
        }
    }
}

void shellSort(std::vector<int>& arr) {
    int n = arr.size();
    int gap = n / 2;
    while (gap > 0) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j = i;
            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
        gap /= 2;
    }
}

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

double measure(void (*sortFunc)(std::vector<int>&), std::vector<int> arr) {
    auto start = std::chrono::high_resolution_clock::now();
    sortFunc(arr);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    return elapsed.count();
}

double measureQuick(std::vector<int> arr) {
    auto start = std::chrono::high_resolution_clock::now();
    quickSort(arr, 0, arr.size() - 1);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    return elapsed.count();
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(0));

    int sizes[] = {1000, 5000, 10000, 50000, 100000, 200000, 500000, 1000000};

    std::cout << "N\t\tCombSort\tShellSort\tQuickSort" << std::endl;

    for (int k = 0; k < 8; k++) {
        int n = sizes[k];
        std::vector<int> base(n);
        for (int i = 0; i < n; i++)
            base[i] = rand() % 10000000;

        double t1 = measure(combSort, base);
        double t2 = measure(shellSort, base);
        double t3 = measureQuick(base);

        std::cout << n << "\t\t" << t1 << "\t\t" << t2 << "\t\t" << t3 << std::endl;
    }

    return 0;
}
