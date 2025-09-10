#include <bits/stdc++.h>

long long DP_L() {
    int n;
    std::cin >> n;
    std::vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    std::vector<std::vector<std::pair<long long, long long>>> dp(n, 
        std::vector<std::pair<long long, long long>>(n));
    for (int i = 0; i < n; i++) {
        dp[i][i].first = a[i];
        dp[i][i].second = -a[i];
    }
    for (int diff = 1; diff < n; diff++) {
        for (int i = 0; i < n - diff; i++) {
            int j = i + diff;
            dp[i][j].first = std::max(dp[i + 1][j].second + a[i], dp[i][j - 1].second + a[j]);
            dp[i][j].second = std::min(dp[i + 1][j].first - a[i], dp[i][j - 1].first - a[j]);
        }
    }
    
    return dp[0][n - 1].first;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cout << DP_L() << "\n";
    return 0;
}