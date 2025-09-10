#include <bits/stdc++.h>

int DP_A() {
    int n;
    std::cin >> n;
    std::vector<int> h(n), c(n);
    for (int i = 0; i < n; i++) {
        std::cin >> h[i];
    }
    c[0] = 0;
    c[1] = std::abs(h[1] - h[0]);
    for (int i = 2; i < n; i++) {
        c[i] = std::min(c[i - 1] + std::abs(h[i] - h[i - 1]), 
            c[i - 2] + std::abs(h[i] - h[i - 2]));
    }
    return c[n - 1];
}

int main() {
    std::cout << DP_A();
    return 0;
}