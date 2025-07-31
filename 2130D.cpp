#include <bits/stdc++.h>

int problem2130D() {
    int n, INF = INT_MAX, ans = 0;
    std::cin >> n;
    std::vector<int> p(n + 1), a(n + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> p[i];
    }
    // TODO: continue

    return ans;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem2130D() << "\n";
    }
    return 0;
}