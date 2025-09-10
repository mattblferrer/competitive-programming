#include <iostream>

void problem2094C() {
    int n;
    std::cin >> n;
    int grid[n][n];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> grid[i][j];
        }
    }
    int p[2*n];
    bool seen[2*n + 1];
    for (int i = 0; i <= 2*n; i++) {
        seen[i] = false;
    }
    for (int i = 0; i < 2*n - 1; i++) {
        p[i + 1] = grid[i / 2][(i + 1) / 2];
        seen[p[i + 1]] = true;
    }
    for (int i = 1; i <= 2*n; i++) {
        if (!seen[i]) {
            p[0] = i;
        }
    }
    for (int i: p) {
        std::cout << i << " ";
    }
    std::cout << "\n";
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        problem2094C();
    }
    return 0;
}