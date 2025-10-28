#include <iostream>
#include <set>
#include <string>
#include <sstream>
#include <numeric>
#include <algorithm>
#include <iterator>

void get_symm_diff(const std::set<int>& setA, const std::set<int>& setB, std::set<int>& result) {
    std::set_symmetric_difference(setA.begin(), setA.end(),
        setB.begin(), setB.end(),
        std::inserter(result, result.begin()));
}

void calc_avg(const std::set<int>& data, double* avg) {
    if (data.empty()) {
        *avg = 0.0;
        return;
    }
    double sum = 0.0;
    for (int val : data) {
        sum += val;
    }
    *avg = sum / data.size();
}

void readSetFromString(std::set<int>& s, const std::string& name) {
    std::cout << "Введите элементы для множества " << name << " через пробел :" << std::endl;

    std::string line;
    std::getline(std::cin, line);

    std::stringstream ss(line);
    int value;

    while (ss >> value) {
        s.insert(value);
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    std::set<int> A, B;

    readSetFromString(A, "A");
    readSetFromString(B, "B");

    std::set<int> result;
    get_symm_diff(A, B, result);

    double avg_value = 0.0;
    calc_avg(result, &avg_value);

    std::cout << "\nСимметрическая разница: { ";
    for (int val : result) {
        std::cout << val << " ";
    }
    std::cout << "}" << std::endl;

    std::cout << "Математическое ожидание: " << avg_value << std::endl;

    system("pause");
    return 0;
}
