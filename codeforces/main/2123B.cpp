#include <bits/stdc++.h>

std::string problem2123B() {
    int n, j, k, m = 0;
    std::cin >> n >> j >> k;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        m = std::max(m, a[i]);
    }
    int a_j = a[j - 1];
    if (k >= 2) return "YES";
    else if (a_j < m) return "NO";
    else return "YES";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem2123B() << "\n";
    }
    return 0;
}