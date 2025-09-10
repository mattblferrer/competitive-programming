#include <bits/stdc++.h>

int DP_H() {
    int h, w, mod = pow(10, 9) + 7;
    std::cin >> h >> w;
    std::vector<std::string> a(h);
    for (int i = 0; i < h; i++) {
        std::cin >> a[i];
    }

    std::vector<std::vector<int>> p(h, std::vector<int>(w));
    p[0][0] = 1;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (a[i][j] == '#') continue;
            if (i == 0 && j == 0) continue;
            else if (i == 0) p[i][j] = p[i][j - 1];
            else if (j == 0) p[i][j] = p[i - 1][j];
            else p[i][j] = (p[i - 1][j] + p[i][j - 1]) % mod;
        }
    }
    return p[h - 1][w - 1];
}

int main() {
    std::cout << DP_H();
    return 0;
}