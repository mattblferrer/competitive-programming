#include <bits/stdc++.h>

int DP_B() {
    int n, k, INF = 1999999999;
    std::cin >> n >> k;
    std::vector<int> h(n), c(n);
    for (int i = 0; i < n; i++) {
        std::cin >> h[i];
    }
    
    c[0] = 0;
    for (int i = 1; i < n; i++) {
        int min = INF;
        for (int j = 1; j <= k; j++) {
            if (i - j < 0) continue;
            min = std::min(min, c[i - j] + std::abs(h[i] - h[i - j]));
        }
        c[i] = min;
    }
    return c[n - 1];
}

int main() {
    std::cout << DP_B();
    return 0;
}