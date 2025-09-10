#include <bits/stdc++.h>

int CSES1636() {
    int n, x, mod = pow(10, 9) + 7;
    std::cin >> n >> x;
    std::vector<int> c(n);
    for (int i = 0; i < n; i++) {
        std::cin >> c[i];
    }
    std::sort(c.begin(), c.end());
    std::vector<int> comb(x + 1);
    comb[0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= x; j++) {
            if (c[i] > j) continue;
            comb[j] = (comb[j] + comb[j - c[i]]) % mod;
        }
    }
    return comb[x];
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cout << CSES1636() << "\n";
    return 0;
}