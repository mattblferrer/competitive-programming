#include <bits/stdc++.h>

int ABC118B() {
    int n, m, k_i, a_ij;
    std::cin >> n >> m;
    std::vector<int> food(m + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> k_i;
        for (int j = 0; j < k_i; j++) {
            std::cin >> a_ij;
            food[a_ij]++;
        }
    }
    int ans = 0;
    for (int i = 1; i <= m; i++) {
        if (food[i] == n) ans++;
    }
    return ans;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cout << ABC118B() << "\n";
    return 0;
}