#include <iostream>
#include <cmath>
#include <algorithm>

double pi = 3.14159;

int main() {
    setlocale(LC_ALL, "Russian");
    double x, y;

    std::cout << "enter x: ";
    std::cin >> x;

    std::cout << "enter y: ";
    std::cin >> y;

    double R = 1.0 / tan((pi / 4.0) * x);
    double S = pow(y, 1.0 / 4.0) * pow(2.0, 1.0 / y);

    double C = std::max(R, S);

    std::cout << "r = " << R << std::endl;
    std::cout << "s = " << S << std::endl;
    std::cout << "c = " << C << std::endl;

    system("pause");
    return 0;
}
