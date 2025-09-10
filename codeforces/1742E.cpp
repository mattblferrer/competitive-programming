#include <iostream>

void problem1742E() {
    long long n, q, a_i, k_i;
    std::cin >> n >> q;
    long long* a_sum = new long long[n + 2];
    long long* a_max = new long long[n + 2];
    long long sum = 0;
    long long max = 0;

    for (long long i = 1; i <= n; i++) {
        std::cin >> a_i;
        sum += a_i;
        max = std::max(max, a_i);
        a_sum[i] = sum;
        a_max[i] = max;
    }
    a_sum[0] = 0;
    a_sum[n + 1] = sum;
    a_max[0] = 0;
    a_max[n + 1] = max;

    for (long long i = 0; i < q; i++) {
        std::cin >> k_i;
        long long left = 0;
        long long right = n + 2;
        while (right - left > 1) {
            long long mid = (left + right) / 2;
            if (k_i < a_max[mid]) {
                right = mid;
            }
            else {
                left = mid;
            }
        }
        std::cout << a_sum[left] << " ";
    }
    std::cout << "\n";
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        problem1742E();
    }
    return 0;
}