#include <iostream>

void problem1916A() {
    long long n, k, b_i;
    std::cin >> n >> k;
    long long prod = 1;

    for (int i = 0; i < n; i++) {
        std::cin >> b_i;
        prod *= b_i;
    }
    if (2023 % prod != 0) {
        std::cout << "NO\n";
        return;
    }
    std::cout << "YES\n" << 2023 / prod;
    for (int i = 0; i < k - 1; i++) {
        std::cout << " " << 1;
    }
    std::cout << "\n";
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        problem1916A();
    }
    return 0;
}