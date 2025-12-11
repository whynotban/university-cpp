#include <iostream>
#include <cmath>
#include <algorithm>
#include <stdexcept>
#include <locale>

void calculate_values(double x, double y, double& R, double& S, double& C) {
    if (y <= 0) {
        throw std::invalid_argument("Invalid y");
    }

    double pi = 3.141592653589793;
    double tan_val = std::tan((pi / 4.0) * x);

    if (std::abs(tan_val) < 0.000001) {
        throw std::invalid_argument("Invalid x");
    }

    R = 1.0 / tan_val;
    S = std::pow(y, 0.25) * std::pow(2.0, 1.0 / y);
    C = std::max(R, S);
}

#ifndef UNIT_TESTING
int main() {
    setlocale(LC_ALL, "Russian");
    double x, y;
    double R, S, C;

    std::cout << "Enter x: ";
    std::cin >> x;
    std::cout << "Enter y: ";
    std::cin >> y;

    try {
        calculate_values(x, y, R, S, C);
        std::cout << "R = " << R << std::endl;
        std::cout << "S = " << S << std::endl;
        std::cout << "C = " << C << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "ошибка: " << e.what() << std::endl;
    }

    return 0;
}
#endif
