#include <bits/stdc++.h>

std::string ABC054B() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::string> a(n), b(m);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    for (int i = 0; i < m; i++) {
        std::cin >> b[i];
    }
    for (int i = 0; i <= n - m; i++) {
        for (int j = 0; j <= n - m; j++) {
            bool match = true;
            for (int k = 0; k < m; k++) {
                for (int l = 0; l < m; l++) {
                    if (a[i + k][j + l] != b[k][l]) match = false;
                }
            }
            if (match) return "Yes";
        }
    }
    return "No";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cout << ABC054B() << "\n";
    return 0;
}