#include <bits/stdc++.h>

void problemB() {
    int** garden = new int*[10001];
    for (int i = 0; i < 10001; i++) {
        garden[i] = new int[10001];
        for (int j = 0; j < 10001; j++) {
            garden[i][j] = 0;
        }
    }

    long long g, x_i, y_i, m, r;
    std::cin >> g;
    for (int i = 0; i < g; i++) {
        std::cin >> x_i >> y_i;
        garden[x_i][y_i]++;
    }
    
    std::cin >> m;
    for (int i = 0; i < m; i++) {
        std::cin >> x_i >> y_i >> r;
        for (long long j = std::max(0LL, x_i - r); j <= std::min(10000LL, x_i + r); j++) {
            for (long long k = std::max(0LL, y_i - r); k <= std::min(10000LL, y_i + r); k++) {
                if ((x_i - j) * (x_i - j) + (y_i - k) * (y_i - k) <= r * r) {
                    g -= garden[j][k];
                    garden[j][k] = 0;
                }
            }
        }
    }
    std::cout << g;
}

int main() {
    problemB();
    return 0;
}