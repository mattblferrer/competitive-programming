#include <iostream>

long long problem1175A() {
    long long n, k;
    std::cin >> n >> k;
    long long steps = 0;
    while (n != 0) {
        steps += n % k + 1;
        n -= n % k;
        n /= k;
    }
    return steps - 1;
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem1175A() << "\n";
    }
    return 0;
}