#include <bits/stdc++.h>

int problem2121A() {
    int n, s;
    std::cin >> n >> s;
    std::vector<int> x(n);
    for (int i = 0; i < n; i++) {
        std::cin >> x[i];
    }
    return std::min(
        std::abs(s - x[0]) + std::abs(x[n - 1] - x[0]),
        std::abs(s - x[n - 1]) + std::abs(x[n - 1] - x[0])
    );
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem2121A() << "\n";
    }
    return 0;
}