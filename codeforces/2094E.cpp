#include <bits/stdc++.h>

long long problem2094E() {
    long long n;
    std::cin >> n;
    std::vector<long long> a(n);
    std::vector<long long> bits(32);
    for (long long i = 0; i < n; i++) {
        std::cin >> a[i];
        for (long long j = 0; j < 31; j++) {
            bits[j] += (a[i] & (1 << j)) >> j;
        }
    }
    
    long long best = 0;
    for (long long i = 0; i < n; i++) {
        long long sum = 0;
        for (long long j = 0; j < 31; j++) {
            if ((a[i] & (1 << j))) sum += (n - bits[j]) * (1 << j);
            else sum += bits[j] * (1 << j);
        }
        best = std::max(best, sum);
    }
    return best;
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem2094E() << "\n";
    }
    return 0;
}