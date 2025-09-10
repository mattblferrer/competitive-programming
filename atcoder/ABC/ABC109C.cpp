#include <iostream>
#include <numeric>

int ABC109C() {
    int n, x;
    std::cin >> n >> x;
    int* c = new int[n];
    for (int i = 0; i < n; i++) {
        std::cin >> c[i];
    }
    int gcd = std::abs(c[0] - x);
    for (int i = 0; i < n; i++) {
        gcd = std::gcd(gcd, std::abs(c[i] - x));
    }
    return gcd;
}

int main() {
    std::cout << ABC109C();
    return 0;
}