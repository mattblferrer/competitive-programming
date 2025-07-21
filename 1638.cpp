#include <bits/stdc++.h>

int CSES1638() {
    int n, mod = pow(10, 9) + 7;
    std::cin >> n;
    std::vector<std::string> grid(n);
    for (int i = 0; i < n; i++) {
        std::cin >> grid[i];
    }
    std::vector<std::vector<int>> dp(n, std::vector<int>(n));
    dp[0][0] = (grid[0][0] == '.');
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0 && j == 0) continue;
            if (grid[i][j] == '*') continue;
            if (i == 0) dp[i][j] = (grid[i][j - 1] == '.') * dp[i][j - 1];
            else if (j == 0) dp[i][j] = (grid[i - 1][j] == '.') * dp[i - 1][j];
            else dp[i][j] = ((grid[i][j - 1] == '.') * dp[i][j - 1] 
                + (grid[i - 1][j] == '.') * dp[i - 1][j]) % mod;
        }
    }
    return dp[n - 1][n - 1];
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cout << CSES1638() << "\n";
    return 0;
}