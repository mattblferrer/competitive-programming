#include <bits/stdc++.h>

void DP_F() {
    std::string s, t;
    std::cin >> s >> t;
    int n = s.size(), m = t.size();
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1));
    std::vector<std::vector<std::pair<int, int>>> lc(n + 1, std::vector<std::pair<int, int>>(m + 1));
    for (int i = n - 1; i >= 0; i--) {
        for (int j = m - 1; j >= 0; j--) {
            if (s[i] == t[j]) {
                dp[i][j] = 1 + dp[i + 1][j + 1];
                lc[i][j] = {i + 1, j + 1};
            }
            else {
                if (dp[i][j + 1] >= dp[i][j]) {
                    dp[i][j] = dp[i][j + 1];
                    lc[i][j] = {i, j + 1};
                }
                if (dp[i + 1][j] >= dp[i][j]) {
                    dp[i][j] = dp[i + 1][j];
                    lc[i][j] = {i + 1, j};
                }
            }
        }
    }
    int i = 0, j = 0; 
    while (i != n && j != m) {
        if (lc[i][j].first == i + 1 && lc[i][j].second == j + 1) {
            std::cout << s[i];
            i++;
            j++;
        }
        else if (lc[i][j].first == i && lc[i][j].second == j + 1) j++;
        else if (lc[i][j].first == i + 1 && lc[i][j].second == j) i++;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    DP_F();
    return 0;
}