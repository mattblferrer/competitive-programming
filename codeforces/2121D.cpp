#include <bits/stdc++.h>

void problem2121D() {
    int n;
    std::cin >> n;
    std::vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        std::cin >> b[i];
    }
    std::vector<std::pair<int, int>> ops;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                ops.push_back({1, j});
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (b[j] > b[j + 1]) {
                ops.push_back({2, j});
                int temp = b[j];
                b[j] = b[j + 1];
                b[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (a[i] > b[i]) {
            ops.push_back({3, i});
            int temp = a[i];
            a[i] = b[i];
            b[i] = temp;
        }
    }
    std::cout << ops.size() << "\n";
    for (const auto& pair: ops) {
        std::cout << pair.first << " " << pair.second + 1 << "\n";
    }
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        problem2121D();
    }
    return 0;
}