#include <bits/stdc++.h>

long long problem2035A() {
    long long n, m, r, c;
    std::cin >> n >> m >> r >> c;
    return (n - r) * (2*m - 1) + (m - c);
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem2035A() << "\n";
    }
    return 0;
}