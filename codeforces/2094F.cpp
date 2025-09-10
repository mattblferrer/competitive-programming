#include <bits/stdc++.h>

void problem2094F() {
    int n, m, k;
    std::cin >> n >> m >> k;
    std::vector<std::vector<int>> vec(n, std::vector<int>(m));
    for (int i = 0; i < n; i++) {
        std::vector<int> row(m);
        for (int j = 0; j < m; j++) {
            row[j] = (i * m + j) % k + 1;
        }
        for (int j = 0; j < m; j++) {
            if (i != 0 && vec[i - 1][j] == row[j]) {
                row.insert(row.begin(), row[m - 1]);
                row.pop_back();
            }
        }
        vec[i] = row;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cout << vec[i][j] << ' ';
        }
        std::cout << '\n';
    }
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        problem2094F();
    }
    return 0;
}