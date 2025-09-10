#include <bits/stdc++.h>

long long problem2047C() {
    int n;
    std::cin >> n;
    std::vector<int> a1(n), a2(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a1[i];
    }
    for (int i = 0; i < n; i++) {
        std::cin >> a2[i];
    }
    int max_min = -9999999, ans = 0;
    for (int i = 0; i < n; i++) {
        ans += std::max(a1[i], a2[i]);
        max_min = std::max(max_min, std::min(a1[i], a2[i]));
    }
    return ans + max_min;
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem2047C() << "\n";
    }
    return 0;
}