#include <cmath>
#include <iostream>

long long ABC046B() {
    long long n, k;
    std::cin >> n >> k;
    return k * std::pow(k - 1, n - 1);
}

int main() {
    std::cout << ABC046B();
    return 0;
}