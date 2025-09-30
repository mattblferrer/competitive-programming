#include <bits/stdc++.h>

int problem2128A() {
    long long n, c, ans = 0;
    std::cin >> n >> c;
    std::vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    std::sort(a.begin(), a.end());
    for (int i = n - 1; i >= 0; i--) {
        if (a[i] <= c) {
            for (int j = 0; j < n; j++) {
                a[j] *= 2;
            }
        }
        else ans++;
    }
    return ans;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem2128A() << "\n";
    }
    return 0;
}