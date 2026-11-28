#include <iostream>

long long ABC046C() {
    long long n;
    std::cin >> n;
    long long* t = new long long[n];
    long long* a = new long long[n];

    for (int i = 0; i < n; i++) {
        std::cin >> t[i] >> a[i];
    }
    long long curr_t = 1;
    long long curr_a = 1;
    long long ratio_t, ratio_a;
    for (int i = 0; i < n; i++) {
        ratio_t = 1 + ((curr_t - 1) / t[i]);
        ratio_a = 1 + ((curr_a - 1) / a[i]);
        curr_t = t[i] * std::max(ratio_t, ratio_a);
        curr_a = a[i] * std::max(ratio_t, ratio_a);
    }
    return curr_t + curr_a;
}

int main() {
    std::cout << ABC046C();
    return 0;
}