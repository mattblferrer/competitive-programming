#include <bits/stdc++.h>

std::vector<bool> is_prime(100001, true);
std::vector<int> lpf(100001, 0);  // largest prime factor

void sieve() {
    for (int i = 2; i <= 100001; i++) {
        for (int j = 2; i * j < 100001; j++) {
            is_prime[i * j] = false;
            lpf[i * j] = i;
        }
    }
    for (int i = 0; i < 100001; i++) {
        if (is_prime[i]) lpf[i] = i;
    }
}

void problem2123F() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        int n;
        std::cin >> n;
        std::vector<int> p(n);
        for (int i = 1; i <= n; i++) {  // generate p
            p[i - 1] = i;
        }
        for (int i = 1; i <= n; i++) {  // swap i with lpf[i] in p
            int temp = p[i - 1];
            p[i - 1] = p[lpf[i] - 1];
            p[lpf[i] - 1] = temp;
        }
        for (int i = 0; i < n; i++) {  // print out p
            std::cout << p[i] << " ";
        }
        std::cout << "\n";
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    sieve();
    problem2123F();
    return 0;
}