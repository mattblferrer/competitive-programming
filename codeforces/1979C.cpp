#include <bits/stdc++.h>

void problem1979C() {
    int n;
    std::cin >> n;
    std::vector<int> k(n);
    for (int i = 0; i < n; i++) {
        std::cin >> k[i];
    }
    std::vector<int> x(n);
    long long lc = 1, s = 0, coins = 0;
    for (int i = 0; i < n; i++) {
        lc = std::lcm(lc, k[i]);
    }
    for (int i = 0; i < n; i++) {
        x[i] = lc / k[i];
        coins += lc / k[i];
    }
    if (coins >= lc) {
        std::cout << "-1\n";
        return;
    }
    for (int i = 0; i < n; i++) {
        std::cout << x[i] << " ";
    }
    std::cout << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        problem1979C();
    }
    return 0;
}