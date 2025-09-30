#include <cmath>
#include <iostream>
#include <string>

bool isPrime(long long n) {
    for (int i = 2; i <= (int)sqrt(n); i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return n > 1;
}

bool problem2093C() {
    long long ones[9] = {1, 11, 111, 1111, 11111, 111111, 1111111, 11111111, 111111111};
    long long x, k;
    std::cin >> x >> k;
    if (k == 1) {
        return isPrime(x);
    }
    else if (x == 1) {
        return isPrime(ones[k - 1]);
    }
    else {
        return false;
    }
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        bool answer = problem2093C();
        if (answer) std::cout << "YES\n";
        else std::cout << "NO\n";
    }
    return 0;
}