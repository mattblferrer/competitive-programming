#include <bits/stdc++.h>

void problem2123C() {
    int n;
    std::cin >> n;
    std::vector<int> a(n), s(n), mini(n), maxi(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    int lo = 9999999, hi = 0;
    for (int i = 0; i < n; i++) {
        lo = std::min(lo, a[i]);
        mini[i] = lo;
    }
    for (int i = n - 1; i >= 0; i--) {
        hi = std::max(hi, a[i]);
        maxi[i] = hi;
    }
    for (int i = 0; i < n; i++) {
        if (a[i] == mini[i]) s[i] = 1;
        if (a[i] == maxi[i]) s[i] = 1;
        std::cout << s[i];
    }
    std::cout << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        problem2123C();
    }
    return 0;
}