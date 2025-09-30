#include <iostream>

int problem2044A() {
    int n;
    std::cin >> n;
    return n - 1;
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem2044A() << '\n';
    }
    return 0;
}