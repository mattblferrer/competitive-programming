#include <iostream>

void problem1454A() {
    int n;
    std::cin >> n;

    if (n % 2 == 0) {
        for (int i = n; i > 0; i--) {
            std::cout << i << " ";
        }
        std::cout << "\n";
    }
    else {
        for (int i = 2; i <= n; i++) {
            std::cout << i << " ";
        }
        std::cout << "1\n";
    }
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        problem1454A();
    }

    return 0;
}