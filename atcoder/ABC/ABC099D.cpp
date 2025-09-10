#include <iostream>

int ABC099D() {
    // input
    int n, c;
    std::cin >> n >> c;
    int** d = new int*[c];
    for (int i = 0; i < c; i++) {
        d[i] = new int[c];
        for (int j = 0; j < c; j++) {
            std::cin >> d[i][j];
        }
    }
    int** color = new int*[n];
    for (int i = 0; i < n; i++) {
        color[i] = new int[n];
        for (int j = 0; j < n; j++) {
            std::cin >> color[i][j];
            color[i][j]--;  // since input 1-indexed
        }
    }

    // calculate
    int** repaint = new int*[3];
    for (int i = 0; i < 3; i++) {
        repaint[i] = new int[c];
        for (int j = 0; j < c; j++) {
            repaint[i][j] = 0;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            repaint[(i + j) % 3][color[i][j]]++; 
        }
    }
    int min_w = 999999999;
    for (int i = 0; i < c; i++) {
        for (int j = 0; j < c; j++) {
            if (i == j) {
                continue;
            }
            for (int k = 0; k < c; k++) {
                if (i == k || j == k) {
                    continue;
                }
                int w = 0;
                for (int l = 0; l < c; l++) {
                    w += d[l][i] * repaint[0][l];
                    w += d[l][j] * repaint[1][l];
                    w += d[l][k] * repaint[2][l];
                }
                min_w = std::min(min_w, w);
            }
        }
    }
    return min_w;
}

int main() { 
    std::cout << ABC099D();
    return 0;
}