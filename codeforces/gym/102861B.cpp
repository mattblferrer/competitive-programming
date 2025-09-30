#include <bits/stdc++.h>

char problem102861B() {
    int n, d, l, r, c;
    std::cin >> n;
    std::vector<std::vector<int>> grid(10, std::vector<int>(10));
    for (int i = 0; i < n; i++) {
        std::cin >> d >> l >> r >> c;
        r--;
        c--;
        if (d == 0) {  // horizontal (rightward)
            for (int j = c; j < c + l; j++) {
                if (j >= 10) return 'N';
                if (grid[r][j] != 0) return 'N';
                grid[r][j] = 1;
            }
        }
        if (d == 1) {  // vertical (downward)
            for (int j = r; j < r + l; j++) {
                if (j >= 10) return 'N';
                if (grid[j][c] != 0) return 'N';
                grid[j][c] = 1;
            }
        }
    }
    return 'Y';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cout << problem102861B();
    return 0;
}