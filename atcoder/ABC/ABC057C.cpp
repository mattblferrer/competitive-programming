#include <cmath>
#include <iostream>

long long ABC057C() {
    long long n;
    std::cin >> n;
    long long min_f = 99999;
    long long f; 

    for (int i = 1; i <= (int)sqrt(n) + 1; i++) {
        if (n % i == 0) {
            f = std::max((int)log10(i), (int)log10(n / i)) + 1;
            min_f = std::min(min_f, f);
        }
    }
    return min_f;
}

int main() {
    std::cout << ABC057C();
    return 0;
}