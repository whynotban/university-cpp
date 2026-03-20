#include <iostream>
#include <cmath>
#include <locale>

double f1(double x) {
    return 3 * x * x - 2;
}

double f2(double x) {
    return -x * x + 6;
}

double simpson(double a, double b, int n) {
    if (n % 2 == 1) n++;
    double h = (b - a) / n;
    double sum = fabs(f1(a) - f2(a)) + fabs(f1(b) - f2(b));

    for (int i = 1; i < n; i += 2)
        sum += 4 * fabs(f1(a + i * h) - f2(a + i * h));

    for (int i = 2; i < n - 1; i += 2)
        sum += 2 * fabs(f1(a + i * h) - f2(a + i * h));

    return (h / 3) * sum;
}

int main() {
    setlocale(LC_ALL, "Russian");

    double a = 2.0, b = 7.0;

    int sizes[] = {
        4, 10, 20, 50, 100,
        200, 500, 1000, 5000,
        10000, 50000, 100000
    };

    std::cout << "N\t\tПлощадь" << std::endl;

    for (int i = 0; i < 12; i++) {
        double area = simpson(a, b, sizes[i]);
        std::cout << sizes[i] << "\t\t" << area << std::endl;
    }

    return 0;
}
