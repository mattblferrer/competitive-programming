#include <bits/stdc++.h>

int problem698A() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    std::vector<std::vector<int>> rest(2, std::vector<int>(n + 1));
    for (int i = 0; i < n; i++) {
        if (a[i] == 0) {
            rest[0][i + 1] = std::min(rest[0][i] + 1, rest[1][i] + 1);
            rest[1][i + 1] = std::min(rest[0][i] + 1, rest[1][i] + 1);
        }
        if (a[i] == 1) {
            rest[0][i + 1] = std::min(rest[0][i] + 1, rest[1][i] + 1);
            rest[1][i + 1] = std::min(rest[0][i], rest[1][i] + 1);
        }
        if (a[i] == 2) {
            rest[0][i + 1] = std::min(rest[0][i] + 1, rest[1][i]);
            rest[1][i + 1] = std::min(rest[0][i] + 1, rest[1][i] + 1);
        }
        if (a[i] == 3) {
            rest[0][i + 1] = std::min(rest[0][i] + 1, rest[1][i]);
            rest[1][i + 1] = std::min(rest[0][i], rest[1][i] + 1);
        }
    }

    return std::min(rest[0][n], rest[1][n]);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cout << problem698A() << "\n";
    return 0;
}