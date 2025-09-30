#include <iostream>
#include <numeric>

int problem2034A() {
    int a, b;
    std::cin >> a >> b;
    return std::lcm(a, b);
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem2034A() << "\n";
    }

    return 0;
}