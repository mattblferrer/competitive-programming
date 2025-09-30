#include <bits/stdc++.h>

std::string problem2123D() {
    int n, k;
    std::string s;
    std::cin >> n >> k >> s;

    int zero = 0, one = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') one++;
        else zero++;
    }
    if (one <= k) return "Alice";
    if (n < 2 * k) return "Alice";
    return "Bob";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem2123D() << "\n";
    }
    return 0;
}