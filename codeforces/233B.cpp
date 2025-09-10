#include <cmath>
#include <iostream>

long long problem233B() {
    long long n;
    std::cin >> n;
    long long x = std::sqrt(n);

    for (long long i = std::max(1LL, x - 100); i < x + 100; i++) {
        long long s = 0;
        long long curr = i;
        while (curr != 0) {
            s += curr % 10;
            curr /= 10;
        } 
        if ((i + s) * i == n) {
            return i;
        }
    }
    return -1;
}

int main() {
    std::cout << problem233B();
    return 0;
}