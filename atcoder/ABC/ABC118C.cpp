#include <bits/stdc++.h>

int ABC118C() {
    int n;
    std::cin >> n;
    std::vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }
    int ans = a[1];
    for (int i = 1; i <= n; i++) {
        ans = std::gcd(ans, a[i]);
    }
    return ans;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cout << ABC118C() << "\n";
    return 0;
}