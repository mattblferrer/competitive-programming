#include <bits/stdc++.h>

void ABC118D() {
    int n, m, a_i, INF = 9999999;
    std::cin >> n >> m;
    std::vector<int> d(10), mt = {INF, 2, 5, 5, 4, 5, 6, 3, 7, 6};
    for (int i = 0; i < m; i++) {
        std::cin >> a_i;
        d[a_i] = 1;
    }
    std::vector<int> dp(n + 1, -INF), last(n + 1);
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 10; j++) {
            if (!d[j]) continue;
            if (mt[j] > i) continue;
            if (dp[i] <= dp[i - mt[j]] + 1) {
                dp[i] = dp[i - mt[j]] + 1;
                last[i] = j;
            }
        }
    }
    while (n > 0) {
        std::cout << last[n];
        n -= mt[last[n]];
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    ABC118D();
    return 0;
}