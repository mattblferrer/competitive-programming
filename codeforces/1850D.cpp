#include <bits/stdc++.h>

int problem1850D() {
    int n, k;
    std::cin >> n >> k;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    std::sort(a.begin(), a.end());
    int m = 1, curr = 1;
    for (int i = 0; i < n - 1; i++) {
        if (a[i + 1] - a[i] > k) curr = 1;
        else curr++;
        m = std::max(m, curr);
    }
    return n - m;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem1850D() << "\n";
    }
    return 0;
}