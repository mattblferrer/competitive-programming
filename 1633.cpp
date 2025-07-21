#include <bits/stdc++.h>

int CSES1633() {
    int n, mod = pow(10, 9) + 7;
    std::cin >> n;
    std::vector<int> dp(n + 1);
    for (int i = 1; i <= std::min(n, 6); i++) {
        dp[i] = 1;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= 6; j++) {
            if (j > i) break;
            dp[i] = (dp[i] + dp[i - j]) % mod;
        }
    }
    return dp[n];
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cout << CSES1633() << "\n";
    return 0;
}