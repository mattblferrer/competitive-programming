#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;

vector<ll> fac;

// helper functions
ll binexp(ll a, ll b, ll mod) {
    ll ans = 1;
    while (b) {
        if (b % 2) {
            ans = (ans * a) % mod;
        }
        a = (a * a) % mod;  
        b >>= 1;
    }
    return ans;
}

ll modinv_p(ll a, ll p) {
    return binexp(a, p - 2, p);
}

void factorial_vec(ll n, ll mod, vector<ll> arr) {
    arr.resize(n + 1);
    arr[0] = 1;
    for (int i = 1; i <= n; i++) {
        arr[i] = arr[i - 1] * i % mod;
    }
}

// main functions
ll comb(ll n, ll k) {
    if (k < 0) return 0;
    if (k == 0) return 1;
    return (n * comb(n - 1, k - 1)) / k;
}

ll factorial(ll n) {
    if (n == 0) return 0;
    return n * factorial(n - 1);
}

ll comb_m(ll n, ll k, ll p) {
    // call factorial_vec(n, p, fac)
    return fac[n] * modinv_p((fac[k] * fac[n - k]) % p, p) % p;
}
