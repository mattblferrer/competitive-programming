#include <bits/stdc++.h>

int CSES1639() {
    std::string s, t;
    std::cin >> s >> t;
    int n = s.size(), m = t.size();
    std::vector<std::vector<int>> d(n + 1, std::vector<int>(m + 1));
    for (int i = 0; i <= n; i++) {
        d[i][0] = i;
    }
    for (int i = 0; i <= m; i++) {
        d[0][i] = i;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int curr = 1;
            if (s[i - 1] == t[j - 1]) curr = 0;
            d[i][j] = std::min({curr + d[i - 1][j - 1], 1 + d[i - 1][j], 1 + d[i][j - 1]});
        }
    }
    return d[n][m];
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cout << CSES1639() << "\n";
    return 0;
}