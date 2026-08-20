#include <bits/stdc++.h>

long long problem2130D() {
    long long n, ans = 0;
    std::cin >> n;
    std::vector<int> p(n + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> p[i];
    }
    for (int i = 1; i <= n; i++) {
        int l = 0, r = 0;
        for (int j = 1; j < i; j++) {
            if (p[j] > p[i]) l++;
        }
        for (int j = i + 1; j <= n; j++) {
            if (p[j] > p[i]) r++;
        }
        ans += std::min(l, r);
    }
    return ans;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem2130D() << "\n";
    }
    return 0;
}