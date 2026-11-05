#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;

vector<ll> fac, inv_fac;

// a^b mod mod, O(log b)
ll binexp(ll a, ll b, ll mod) {
    ll ans = 1;
    a %= mod;
    while (b) {
        if (b % 2) {
            ans = (ans * a) % mod;
        }
        a = (a * a) % mod;
        b >>= 1;
    }
    return ans;
}

// inverse of a mod prime p (Fermat), O(log p)
ll modinv_p(ll a, ll p) {
    return binexp(a, p - 2, p);
}

// exact nCk without a modulus, O(k); n * C(n - 1, k - 1) must fit in ll
ll comb(ll n, ll k) {
    if (k < 0) return 0;
    if (k == 0) return 1;
    return (n * comb(n - 1, k - 1)) / k;
}

// O(n) precompute factorials up to n; mod must be a prime > n
void init_fac(int n, ll mod) {
    fac.assign(n + 1, 1);
    inv_fac.assign(n + 1, 1);
    for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % mod;
    inv_fac[n] = modinv_p(fac[n], mod);
    for (int i = n; i > 0; i--) inv_fac[i - 1] = inv_fac[i] * i % mod;
}

// O(1) nCk mod p, requires init_fac(N, mod) with N >= n
ll comb_f(ll n, ll k, ll mod) {
    if (k < 0 || k > n) return 0;
    return fac[n] * inv_fac[k] % mod * inv_fac[n - k] % mod;
}

// O(k) nCk mod p without precomputation, useful when n is huge but k is small
ll comb_m(ll n, ll k, ll mod) {
    if (k < 0) return 0;
    if (k == 0) return 1;
    ll num = 1, denom = 1;
    for (ll i = n; i >= n - k + 1; i--) num = (num * (i % mod)) % mod;
    for (ll i = 1; i <= k; i++) denom = (denom * i) % mod;
    return (num * modinv_p(denom, mod)) % mod;
}

// exact n! without a modulus (overflows for n > 20), O(n)
ll factorial(ll n) {
    if (n == 0) return 1;
    return n * factorial(n - 1);
}
