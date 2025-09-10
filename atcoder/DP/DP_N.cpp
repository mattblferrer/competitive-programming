#include <bits/stdc++.h>

long long DP_N() {
    long long n, INF = LLONG_MAX;
    std::cin >> n;
    std::vector<long long> pref(n + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> pref[i];
        pref[i] += pref[i - 1];
    }
    std::vector<std::vector<long long>> dp(n, std::vector<long long>(n, INF));
    for (int i = 0; i < n; i++) {
        dp[i][i] = 0;
    }
    for (int s = 1; s < n; s++) {
        for (int i = 0; i + s < n; i++) {
            int l = i, r = i + s;
            for (int j = i; j < r; j++) {
                long long curr = dp[l][j] + dp[j + 1][r] + pref[r + 1] - pref[l];
                dp[l][r] = std::min(dp[l][r], curr);
            }
        }
    }
    return dp[0][n - 1];
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cout << DP_N() << "\n";
    return 0;
}