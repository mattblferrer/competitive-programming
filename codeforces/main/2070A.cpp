#include <iostream>

int problem2070A() {
    int n;
    std::cin >> n;
    return 3 * ((n + 1) / 15) + std::min((n + 1) % 15, 3);
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem2070A() << "\n";
    }
    return 0;
}