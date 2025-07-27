#include <bits/stdc++.h>

std::string problem2128C() {
    int n;
    std::cin >> n;
    std::vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        std::cin >> b[i];
    }
    int rm = b[0];
    for (int i = 0; i < n - 1; i++) {
        rm = std::min(rm, b[i]);
        if (b[i] < b[i + 1] && rm * 2 <= b[i + 1]) return "NO";
    }
    return "YES";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem2128C() << "\n";
    }
    return 0;
}