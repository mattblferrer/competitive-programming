#include <iostream>

void problem233A() {
    int n;
    std::cin >> n;
    if (n % 2 == 1) {
        std::cout << -1;
        return;
    }
    for (int i = 1; i < n; i += 2) {
        std::cout << i + 1 << " " << i << " ";
    }
}

int main() {
    problem233A();

    return 0;
}