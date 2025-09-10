#include <bits/stdc++.h>

long long CSES1643() {
    long long n, INF = powl(10, 18);
    std::cin >> n;
    std::vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    long long ans = -INF, curr = 0;
    for (int i = 0; i < n; i++) {
        curr = std::max(a[i], curr + a[i]);
        ans = std::max(ans, curr);
    }
    return ans;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cout << CSES1643() << "\n";
    return 0;
}