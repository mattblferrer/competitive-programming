#include <bits/stdc++.h>

std::string problem2122A() {
    int n, m;
    std::cin >> n >> m;
    if (n > 2 && m >= 2) return "YES";
    if (m > 2 && n >= 2) return "YES";
    return "NO";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem2122A() << "\n";
    }
    return 0;
}