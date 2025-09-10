#include <iostream>

long long problem1283B() {
    long long n, k;
    std::cin >> n >> k;
    return n - n % k + std::min(n % k, k / 2);
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem1283B() << std::endl;
    }

    return 0;
}