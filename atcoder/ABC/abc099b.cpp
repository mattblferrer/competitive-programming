#include <iostream>

int ABC099B() {
    int a, b;
    std::cin >> a >> b;
    int h_b = (b - a) * (b - a + 1) / 2;
    return h_b - b;
}

int main() { 
    std::cout << ABC099B();
    return 0;
}