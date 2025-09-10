#include <bits/stdc++.h>

int CSES1635() {
    int n, x, mod = pow(10, 9) + 7;
    std::cin >> n >> x;
    std::vector<int> c(n);
    for (int i = 0; i < n; i++) {
        std::cin >> c[i];
    }
    std::sort(c.begin(), c.end());
    std::vector<int> comb(x + 1);
    comb[0] = 1;
    for (int i = 0; i <= x; i++) {
        for (int j = 0; j < n; j++) {
            if (c[j] > i) break;
            comb[i] = (comb[i] + comb[i - c[j]]) % mod;
        }
    }
    return comb[x];
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cout << CSES1635() << "\n";
    return 0;
}