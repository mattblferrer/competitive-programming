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

long long CSES1617() {
    long long n, mod = pow(10, 9) + 7;
    std::cin >> n;
    return binexp(2, n, mod);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cout << CSES1617() << "\n";
    return 0;
}