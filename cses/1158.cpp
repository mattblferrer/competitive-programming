#include <bits/stdc++.h>

long long CSES1158() {
    int n, x;
    std::cin >> n >> x;
    std::vector<int> h(n + 1), s(n + 1);
    std::vector<std::vector<int>> p(n + 1, std::vector<int>(x + 1));
    for (int i = 1; i <= n; i++) {
        std::cin >> h[i];
    }
    for (int i = 1; i <= n; i++) {
        std::cin >> s[i];
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= x; j++) {
            if (j < h[i]) {
                p[i][j] = p[i - 1][j];
            }
            else {
                p[i][j] = std::max(p[i - 1][j], s[i] + p[i - 1][j - h[i]]);
            }
            
        }
    }
    return p[n][x];
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cout << CSES1158() << "\n";
    return 0;
}