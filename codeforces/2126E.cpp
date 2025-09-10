#include <bits/stdc++.h>

std::string problem2126E() {
    int n;
    std::cin >> n;
    std::vector<int> p(n), s(n);
    for (int i = 0; i < n; i++) {
        std::cin >> p[i];
    }
    for (int i = 0; i < n; i++) {
        std::cin >> s[i];
    }
    if (p[n - 1] != s[0]) return "NO";
    for (int i = 0; i < n - 1; i++) {
        if (p[i] % p[i + 1] != 0) return "NO";
        if (s[i + 1] % s[i] != 0) return "NO";
        if (std::gcd(p[i], s[i + 1]) != s[0]) return "NO";
    }
    return "YES";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem2126E() << "\n";
    }
    return 0;
}