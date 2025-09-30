#include <bits/stdc++.h>

long long problem2122B() {
    int n, a_i, b_i, c_i, d_i;
    std::cin >> n;
    std::vector<std::vector<int>> piles;
    for (int i = 0; i < n; i++) {
        std::cin >> a_i >> b_i >> c_i >> d_i;
        piles.push_back({a_i, b_i, c_i, d_i});
    }
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        a_i = piles[i][0], b_i = piles[i][1], c_i = piles[i][2], d_i = piles[i][3];
        if (d_i < b_i) ans += a_i + b_i - d_i;
        else if (c_i < a_i) ans += a_i - c_i;
    }
    return ans;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem2122B() << "\n";
    }
    return 0;
}