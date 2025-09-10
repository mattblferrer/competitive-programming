#include <bits/stdc++.h>

int problem2120B() {
    int n, s, d_x, d_y, x_i, y_i, ans = 0;
    std::cin >> n >> s;
    for (int i = 0; i < n; i++) {
        std::cin >> d_x >> d_y >> x_i >> y_i;
        if (d_x == d_y && x_i == y_i) ans++;
        if (d_x != d_y && x_i == s - y_i) ans++;
    }
    return ans;
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem2120B() << "\n";
    }
    return 0;
}