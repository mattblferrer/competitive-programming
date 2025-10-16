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

// main functions
ll comb(ll n, ll k) {
    if (k < 0) return 0;
    if (k == 0) return 1;
    return (n * comb(n - 1, k - 1)) / k;
}

ll comb_m(ll n, ll k, ll mod) {
    if (k < 0) return 0;
    if (k == 0) return 1;
    ll num = 1, denom = 1;
    for (ll i = n; i >= n - k + 1; i--) num = (num * i) % mod;
    for (ll i = 1; i <= k; i++) denom = (denom * i) % mod;
    return (num * modinv_p(denom, mod)) % mod;
}

ll factorial(ll n) {
    if (n == 0) return 0;
    return n * factorial(n - 1);
}
