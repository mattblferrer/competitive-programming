#include <bits/stdc++.h>

int CSES1637() {
    int n, INF = 2 * pow(10, 9);
    std::cin >> n;
    std::vector<int> dp(n + 1, INF);
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        int j = i;
        std::vector<int> digits;
        while (j > 0) {
            digits.push_back(j % 10);
            j /= 10;
        }
        for (int d: digits) {
            if (i - d < 0) continue;
            dp[i] = std::min(dp[i], dp[i - d] + 1); 
        }
    }
    return dp[n];
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cout << CSES1637() << "\n";
    return 0;
}