#include <bits/stdc++.h>

void problem1985D() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::string> grid(n);
    std::vector<int> rows(n), cols(m);
    for (int i = 0; i < n; i++) {
        std::cin >> grid[i];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '#') {
                rows[i]++;
                cols[j]++;
            }
        }
    }
    int max_rows = 0, rows_i = 0, max_cols = 0, cols_i = 0;
    for (int i = 0; i < n; i++) {
        if (rows[i] > max_rows) {
            max_rows = rows[i];
            rows_i = i;
        }
    }
    for (int i = 0; i < m; i++) {
        if (cols[i] > max_cols) {
            max_cols = cols[i];
            cols_i = i;
        }
    }
    std::cout << rows_i + 1 << " " << cols_i + 1 << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        problem1985D();
    }
    return 0;
}