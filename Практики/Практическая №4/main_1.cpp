#include <iostream>
#include <vector>
#include <clocale>

int main() {
    setlocale(LC_ALL, "Russian");

    const int N = 5;
    std::vector<int> A(N);
    std::vector<int> B(N);
    int t;

    std::cout << "Введите пороговое значение t: ";
    std::cin >> t;

    std::cout << "Введите " << N << " элементов для массива A: ";
    for (int i = 0; i < N; ++i) {
        std::cin >> A[i];
    }

    std::cout << "Введите " << N << " элементов для массива B: ";
    for (int i = 0; i < N; ++i) {
        std::cin >> B[i];
    }

    int countA = 0;
    for (int element : A) {
        if (element < t) {
            countA++;
        }
    }

    int countB = 0;
    for (int element : B) {
        if (element < t) {
            countB++;
        }
    }

    std::cout << "Количество элементов < " << t << " в A: " << countA << std::endl;
    std::cout << "Количество элементов < " << t << " в B: " << countB << std::endl;

    if (countA <= countB) {
        std::cout << "Массив с наименьшим количеством элементов: A" << std::endl;
        for (int element : A) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
        for (int element : B) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
    else {
        std::cout << "Массив с наименьшим количеством элементов: B" << std::endl;
        for (int element : B) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
        for (int element : A) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
