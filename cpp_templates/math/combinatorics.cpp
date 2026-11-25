// Contents
//   binexp              a^b mod mod, O(log b)
//   modinv_p            inverse of a mod prime p (Fermat), O(log p)
//   comb                exact nCk without a modulus, O(k); n * C(n - 1, k - 1) must fit in ll
//   init_fac            O(n) precompute factorials up to n; mod must be a prime > n
//   comb_f              O(1) nCk mod p, requires init_fac(N, mod) with N >= n
//   comb_m              O(k) nCk mod p without precomputation, useful when n is huge but k is small
//   factorial           exact n! without a modulus (overflows for n > 20), O(n)
//   lucas               nCk mod a prime p (Lucas), O(p) once per p, then O(log_p n) per call
//   CombAny             nCk mod any m (Granville + CRT), O(m) tables, then O(log n) per query per prime power
//   OrderTree           helper for permutations: which of 0..n-1 are still available
//   perm_to_factoradic  factoradic digits of a permutation of 0..n-1
//   factoradic_to_perm  inverse of perm_to_factoradic, O(n log n)
//   kth_permutation     k-th permutation of 0..n-1 in lexicographic order (0-indexed); k is taken mod n!
//   derangements        derangements (Montmort numbers) d[0..n] mod any mod, O(n)
//   distinct_subsequences  number of distinct non-empty subsequences of a sequence mod mod, O(n log n)

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

// nCk mod any m >= 1 (Granville + CRT over the prime powers p^e dividing m); m should be small, m^2 must fit in ll
//   CombAny(m)    tables for each p^e, O(m)
//   (n, k)        nCk mod m for any n, k fitting in ll, O(sum over p^e of log_p n + log m)
struct CombAny {
    struct PP { ll p, pe; vector<ll> f; };  // f[i] = product of 1..i without the multiples of p, mod pe
    ll m;
    vector<PP> pps;

    CombAny(ll m): m(m) {
        ll rest = m;
        for (ll p = 2; rest > 1; p++) {
            if (p * p > rest) p = rest;
            if (rest % p) continue;
            ll pe = 1;
            while (rest % p == 0) rest /= p, pe *= p;
            vector<ll> f(pe, 1);
            for (ll i = 1; i < pe; i++) f[i] = i % p ? f[i - 1] * i % pe : f[i - 1];
            pps.push_back({p, pe, f});
        }
    }

    ll operator()(ll n, ll k) const {
        if (k < 0 || k > n || m == 1) return 0;
        ll ans = 0, modulus = 1;
        for (auto &[p, pe, f] : pps) {
            ll e = 0, phi = pe / p * (p - 1);
            auto fact = [&](ll x, int sign) {  // unit part of x! mod pe; adds sign * (power of p in x!) to e
                ll r = 1;
                for (; x > 0; x /= p) {
                    r = r * f[x % pe] % pe;
                    if (x / pe % 2) r = r * f[pe - 1] % pe;  // f[pe - 1] is +-1, so f[pe - 1]^(x / pe) is a sign
                    e += sign * (x / p);
                }
                return r;
            };
            ll cur = fact(n, 1) * binexp(fact(k, -1) * fact(n - k, -1) % pe, phi - 1, pe) % pe;
            cur = cur * binexp(p, e, pe) % pe;
            ll t = ((cur - ans) % pe + pe) % pe * binexp(modulus % pe, phi - 1, pe) % pe;  // merge with CRT
            ans += modulus * t;
            modulus *= pe;
        }
        return ans % m;
    }
};

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

// derangements (Montmort numbers) mod any mod >= 1: d[k] = permutations of k elements with no fixed point, k = 0..n,
// from d[k] = (k - 1)(d[k - 1] + d[k - 2]); n * mod must fit in ll, O(n)
vector<ll> derangements(int n, ll mod) {
    vector<ll> d(n + 1, 0);
    d[0] = 1 % mod;
    for (ll k = 2; k <= n; k++) d[k] = (k - 1) * ((d[k - 1] + d[k - 2]) % mod) % mod;
    return d;
}

// number of distinct non-empty subsequences of a (a string, or a vector of any comparable type) mod mod; add 1 for
// the empty one. f counts them with the empty one: appending x doubles f, minus the ones that already ended in x,
// which number f just before x last appeared, O(n log n)
template <class S>
ll distinct_subsequences(const S &a, ll mod) {
    map<typename S::value_type, ll> last;  // last[x] = f just before the latest x
    ll f = 1 % mod;
    for (const auto &x : a) {
        ll g = (2 * f - last[x] + mod) % mod;
        last[x] = f;
        f = g;
    }
    return (f - 1 + mod) % mod;
}
