#include <bits/stdc++.h>

std::string problem1999C() {
    int n, s, m, l_i, r_i;
    std::cin >> n >> s >> m;
    std::vector<std::pair<int, int>> t(n + 2);
    for (int i = 1; i <= n; i++) {
        std::cin >> l_i >> r_i;
        t[i] = {l_i, r_i};
    }
    t[0] = {0, 0};
    t[n + 1] = {m, m};
    for (int i = 1; i < n + 2; i++) {
        if (t[i - 1].second + s <= t[i].first) return "YES";
    }
    return "NO";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem1999C() << "\n";
    }
    return 0;
}