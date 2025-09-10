#include <iostream>

int ABC057A() {
    int a, b;
    std::cin >> a >> b;
    return (a + b) % 24;
}

int main() {
    std::cout << ABC057A();
    return 0;
}