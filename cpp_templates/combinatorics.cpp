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

// nCk mod a prime p (Lucas), O(p) once per p, then O(log_p n) per call
ll lucas(ll n, ll k, ll p) {
    static vector<ll> f;
    static ll last = 0;
    if (last != p) {
        last = p;
        f.assign(p, 1);
        for (ll i = 1; i < p; i++) f[i] = f[i - 1] * i % p;
    }
    ll res = 1;
    for (; n || k; n /= p, k /= p) {
        ll a = n % p, b = k % p;
        if (b > a) return 0;
        res = res * f[a] % p * modinv_p(f[b] * f[a - b] % p, p) % p;
    }
    return res;
}

// nCk mod any m (Granville + CRT), O(sum of p^e + log n) over the prime powers p^e dividing m; m should be small, m^2 must fit in ll
ll comb_any(ll n, ll k, ll m) {
    if (k < 0 || k > n) return 0;
    ll ans = 0, modulus = 1, rest = m;
    for (ll p = 2; rest > 1; p++) {
        if (p * p > rest) p = rest;
        if (rest % p) continue;
        ll pe = 1;
        while (rest % p == 0) {
            rest /= p;
            pe *= p;
        }
        vector<ll> f(pe, 1);  // f[i] = product of 1..i without the multiples of p, mod pe
        for (ll i = 1; i < pe; i++) f[i] = i % p ? f[i - 1] * i % pe : f[i - 1];
        ll phi = pe / p * (p - 1);
        auto fact = [&](ll x, ll &exp) {  // x! = p^exp * (returned unit) mod pe
            ll r = 1;
            for (; x > 0; x /= p) {
                r = r * binexp(f[pe - 1], x / pe, pe) % pe * f[x % pe] % pe;
                exp += x / p;
            }
            return r;
        };
        ll en = 0, ek = 0, er = 0;
        ll a = fact(n, en), b = fact(k, ek), c = fact(n - k, er);
        ll e = en - ek - er;
        ll cur = a * binexp(b * c % pe, phi - 1, pe) % pe;
        cur = cur * binexp(p, e, pe) % pe;
        ll t = ((cur - ans) % pe + pe) % pe * binexp(modulus % pe, phi - 1, pe) % pe;  // merge with CRT
        ans += modulus * t;
        modulus *= pe;
    }
    return m == 1 ? 0 : ans % m;
}

// helper for permutations: which of 0..n-1 are still available
//   OrderTree(n)      all of 0..n-1 available, O(n)
//   add(i, v)         change the count at i by v, O(log n)
//   less(i)           number of available values below i, O(log n)
//   kth(k)            k-th smallest available value (0-indexed), O(log n)
struct OrderTree {
    int n;
    vector<int> t;

    OrderTree(int n): n(n), t(n + 1, 0) {
        for (int i = 1; i <= n; i++) t[i] = i & -i;
    }

    void add(int i, int v) {
        for (i++; i <= n; i += i & -i) t[i] += v;
    }

    int less(int i) const {
        int res = 0;
        for (; i > 0; i -= i & -i) res += t[i];
        return res;
    }

    int kth(int k) const {
        int p = 0;
        for (int b = n ? __lg(n) : 0; b >= 0 && n; b--) {
            if (p + (1 << b) <= n && t[p + (1 << b)] <= k) {
                p += 1 << b;
                k -= t[p];
            }
        }
        return p;
    }
};

// factoradic digits of a permutation of 0..n-1: d[i] = number of later elements smaller than p[i], O(n log n)
vector<int> perm_to_factoradic(const vector<int> &p) {
    OrderTree tree(p.size());
    vector<int> d(p.size());
    for (int i = 0; i < (int)p.size(); i++) {
        d[i] = tree.less(p[i]);
        tree.add(p[i], -1);
    }
    return d;
}

// inverse of perm_to_factoradic, O(n log n)
vector<int> factoradic_to_perm(const vector<int> &d) {
    OrderTree tree(d.size());
    vector<int> p(d.size());
    for (int i = 0; i < (int)d.size(); i++) {
        p[i] = tree.kth(d[i]);
        tree.add(p[i], -1);
    }
    return p;
}

// k-th permutation of 0..n-1 in lexicographic order (0-indexed); k is taken mod n!, O(n log n)
vector<int> kth_permutation(int n, ll k) {
    vector<int> d(n);
    for (int i = 1; i <= n; i++) {
        d[n - i] = k % i;
        k /= i;
    }
    return factoradic_to_perm(d);
}
