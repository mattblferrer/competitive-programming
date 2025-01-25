#include <cmath>
#include <iostream>
#include <vector>

bool is_prime(int n) {
    for (int i = 2; i < n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return n > 1;
}

int ABC114D() {
    int n;
    std::cin >> n;
    std::vector<int> primes;
    int div = 0;

    for (int i = 2; i < 100; i++) {
        if (is_prime(i)) {
            primes.push_back(i);
        }
    }
    // TODO: solve 
    return div;
}

int main() {
    std::cout << ABC114D();
    return 0;
}