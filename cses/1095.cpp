#include <bits/stdc++.h>

long long binexp(long long a, long long b, long long mod) {
    long long ans = 1;
    while (b > 0) {
        if (b % 2 == 1) {
            ans = (ans * a) % mod;
            b--;
        }
        a = (a * a) % mod;  
        b >>= 1;
    }
    return ans;
}

long long CSES1095() {
    long long a, b, mod = pow(10, 9) + 7;
    std::cin >> a >> b;
    return binexp(a, b, mod);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << CSES1095() << "\n";
    }
    return 0;
}