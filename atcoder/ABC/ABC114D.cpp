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

    for (int i = 2; i <= n; i++) {
        if (is_prime(i)) {
            primes.push_back(i);
        }
    }
    int p = primes.size();
    int* count = new int[p];
    for (int i = 0; i < p; i++) {
        count[i] = 0;
    }
    for (int i = 0; i < p; i++) {
        for (int j = 1; j <= n; j++) {
            int num = j;
            while (num % primes[i] == 0) {
                count[i]++;
                num /= primes[i];
            } 
        }
    }
    for (int i = 0; i < p; i++) {  // a^74
        if (count[i] >= 74) {
            div++;
        }
    }
    for (int i = 0; i < p; i++) {  
        if (count[i] >= 24) {  // a^24*b^2
            for (int j = 0; j < p; j++) {
                if (count[j] >= 2 && i != j) {
                    div++;
                }
            }
        }
        if (count[i] >= 14) {  // a^14*b^4
            for (int j = 0; j < p; j++) {
                if (count[j] >= 4 && i != j) {
                    div++;
                }
            }
        }
    }
    for (int i = 0; i < p; i++) {  // a^4*b^4*c^2
        if (count[i] >= 4) {
            for (int j = 0; j < i; j++) {
                if (count[j] >= 4) {
                    for (int k = 0; k < p; k++) {
                        if (count[k] >= 2 && i != k && j != k) {
                            div++;
                        }
                    }
                }
            }
        }
    }

    return div;
}

int main() {
    std::cout << ABC114D();
    return 0;
}