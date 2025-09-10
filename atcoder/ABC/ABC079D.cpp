#include <iostream>

long long ABC079D() {
    long long h, w;
    std::cin >> h >> w;
    long long** c = new long long*[10];
    for (int i = 0; i <= 9; i++) {
        c[i] = new long long[10];
        for (int j = 0; j <= 9; j++) {
            std::cin >> c[i][j];
        }
    } 
    long long** a = new long long*[h];
    for (int i = 0; i < h; i++) {
        a[i] = new long long[w];
        for (int j = 0; j < w; j++) {
            std::cin >> a[i][j];
        }
    }

    long long mp = 0;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            for (int k = 0; k < 10; k++) {
                for (int l = 0; l < 10; l++) {
                    if (j == k || k == l || j == l) {
                        continue;
                    }
                    c[j][l] = std::min(c[j][k] + c[k][l], c[j][l]);
                }
            }
        }
    }
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (a[i][j] == -1) {
                continue;
            }
            mp += c[a[i][j]][1];
        }
    }
    return mp;
}

int main() {
    std::cout << ABC079D();
    return 0;
}