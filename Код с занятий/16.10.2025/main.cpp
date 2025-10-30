#include <iostream>
#include <cctype>

bool is_upper(char c)
{
    return std::isupper(static_cast<unsigned char>(c));
}

int main()
{
    setlocale(LC_ALL, "Russian");
    char a;
    std::cout << "Введите символ для проверки: ";
    std::cin >> a;
    bool result = is_upper(a);
    std::cout << std::boolalpha;
    std::cout << "заглавная буква: " << result << std::endl;

    return 0;
}
