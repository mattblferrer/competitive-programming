#include <bits/stdc++.h>

int ABC054D() {
    int INF = 100000000;
    int n, m_a, m_b, a_i, b_i, c_i, max_a = 0, max_b = 0;
    std::cin >> n >> m_a >> m_b;
    std::vector<std::vector<int>> chem(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a_i >> b_i >> c_i;
        chem[i] = {a_i, b_i, c_i};
        max_a = std::max(max_a, a_i);
        max_b = std::max(max_b, b_i);
    }
    std::vector<std::vector<std::vector<int>>> dp(n + 1, 
        std::vector<std::vector<int>>(max_a * n + 1, 
        std::vector<int>(max_b * n + 1, INF)));
    dp[0][0][0] = 0; 
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= max_a * n; j++) {
            for (int k = 0; k <= max_b * n; k++) {
                a_i = chem[i - 1][0], b_i = chem[i - 1][1], c_i = chem[i - 1][2];
                if (a_i > j || b_i > k) dp[i][j][k] = dp[i - 1][j][k];
                else dp[i][j][k] = std::min({dp[i - 1][j][k], dp[i - 1][j - a_i][k - b_i] + c_i});
            }
        }
    }
    int ans = INF;
    for (int i = 1; i <= max_a * n; i++) {
        if (i * m_a > max_a * n || i * m_b > max_b * n) break;
        ans = std::min(ans, dp[n][i * m_a][i * m_b]);
    }
    if (ans == INF) return -1;
    return ans;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cout << ABC054D() << "\n";
    return 0;
}