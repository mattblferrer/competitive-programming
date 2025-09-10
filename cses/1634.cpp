#include <bits/stdc++.h>

int CSES1634() {
    int n, x, mod = pow(10, 9) + 7;
    std::cin >> n >> x;
    std::vector<int> c(n);
    for (int i = 0; i < n; i++) {
        std::cin >> c[i];
    }
    std::sort(c.begin(), c.end());
    std::vector<int> dp(x + 1, mod);
    dp[0] = 0;
    for (int i = 1; i <= x; i++) {
        for (int j = 0; j < n; j++) {
            if (c[j] > i) break;
            if (dp[i - c[j]] == mod) continue;
            dp[i] = std::min(dp[i], (1 + dp[i - c[j]]) % mod);
        }
    }
    if (dp[x] == mod) return -1;
    return dp[x];
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cout << CSES1634() << "\n";
    return 0;
}