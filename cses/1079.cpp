#include <bits/stdc++.h>
using ll = long long;
using pll = std::pair<long long, long long>;
ll MOD = pow(10, 9) + 7;

std::vector<long long> fac;

void factorial_vec(long long n, long long mod, std::vector<long long>& arr) {
    arr.resize(n + 1);
    arr[0] = 1;
    for (int i = 1; i <= n; i++) {
        arr[i] = arr[i - 1] * i % mod;
    }
}

long long binexp(long long a, long long b, long long mod) {
    long long ans = 1;
    while (b) {
        if (b % 2) {
            ans = (ans * a) % mod;
        }
        a = (a * a) % mod;  
        b >>= 1;
    }
    return ans;
}

long long modinv_p(long long a, long long p) {
    return binexp(a, p - 2, p);
}

long long comb_m(long long n, long long k, long long p) {
    return fac[n] * modinv_p((fac[k] * fac[n - k]) % p, p) % p;
}

ll CSES1079() {
    ll a, b;
    std::cin >> a >> b;
    return comb_m(a, b, MOD);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    factorial_vec(pow(10, 6) + 1, MOD, fac);
    ll n;
    std::cin >> n;
    for (ll i = 0; i < n; i++) {
        std::cout << CSES1079() << "\n";
    }
    return 0;
}