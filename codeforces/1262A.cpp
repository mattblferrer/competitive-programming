#include <bits/stdc++.h>

int problem1262A() {
    int n;
    std::cin >> n;
    int l_i, r_i, max_l = 0, min_r = 1999999999;
    for (int i = 0; i < n; i++) {
        std::cin >> l_i >> r_i;
        max_l = std::max(max_l, l_i);
        min_r = std::min(min_r, r_i);
    }
    return std::max(0, max_l - min_r);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem1262A() << "\n";
    }
    return 0;
}