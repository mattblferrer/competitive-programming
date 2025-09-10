#include <bits/stdc++.h>

std::string problem2131E() {
    int n;
    std::cin >> n;
    std::vector<int> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        std::cin >> b[i];
    }
    for (int i = 1; i <= n; i++) {
        if (a[i] == b[i]) continue;
        if (i != n) {
            if ((a[i] ^ a[i + 1]) == b[i]) continue;
            if ((a[i] ^ b[i + 1]) == b[i]) continue;
        }
        return "NO";
    }
    return "YES";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem2131E() << "\n";
    }
    return 0;
}