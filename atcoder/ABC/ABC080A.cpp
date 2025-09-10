#include <iostream>

int ABC080A() {
    int n, a, b;
    std::cin >> n >> a >> b;
    return std::min(n * a, b);
}

int main() {
    std::cout << ABC080A();
    return 0;
}