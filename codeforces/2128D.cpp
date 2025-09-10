#include <bits/stdc++.h>

long long problem2128D() {
    long long n;
    std::cin >> n;
    std::vector<int> p(n);
    for (int i = 0; i < n; i++) {
        std::cin >> p[i];
    }
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += i * (n - i + 1);
    }
    for (int i = 0; i < n - 1; i++) {
        if (p[i] < p[i + 1]) ans -= (i + 1) * (n - i - 1);
    }
    return ans;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem2128D() << "\n";
    }
    return 0;
}