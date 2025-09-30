#include <bits/stdc++.h>

int problem1985C() {
    int n;
    std::cin >> n;
    std::vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    long long m = 0, sum = 0, ans = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
        m = std::max(m, a[i]);
        if (m * 2 == sum) ans++;
    }
    return ans;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem1985C() << "\n";
    }
    return 0;
}