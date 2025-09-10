#include <bits/stdc++.h>

int problem106C() {
    int n, m, c_0, d_0, a_i, b_i, c_i, d_i;
    std::cin >> n >> m >> c_0 >> d_0;
    std::vector<std::vector<int>> s(m + 1);
    for (int i = 1; i <= m; i++) {
        std::cin >> a_i >> b_i >> c_i >> d_i;
        s[i] = {a_i, b_i, c_i, d_i};
    }
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            for (int k = 0; k <= s[j][0] / s[j][1]; k++) {
                if (i - s[j][2] * k < 0) break;
                dp[i][j] = std::max(dp[i][j], dp[i - s[j][2] * k][j - 1] + s[j][3] * k);
            }
        }
    }
    int ans = 0;
    for (int i = 0; i <= n; i++) {
        ans = std::max(ans, dp[i][m] + (n - i) / c_0 * d_0);
    }
    return ans;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cout << problem106C() << "\n";
    return 0;
}