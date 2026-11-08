#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;

// a^b mod mod, O(log b)
ll binexp(ll a, ll b, ll mod) {
    ll ans = 1;
    a %= mod;
    while (b) {
        if (b & 1) ans = ans * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ans;
}

// number theoretic transform, each MOD and ROOT pair is its own type:
//   using ntt1 = NTT<998'244'353, 3>;
//   using ntt2 = NTT<469'762'049, 3>;
//   vector<ll> c = ntt1::multiply(a, b);
// MOD must be a prime below 2^31 and ROOT a primitive root of MOD
// the largest transform size is the largest power of 2 dividing MOD - 1
// choices of (MOD, ROOT), max size:
//   (998'244'353, 3), 2^23
//   (469'762'049, 3), 2^26
//   (167'772'161, 3), 2^25
//   (754'974'721, 11), 2^24
//   (1'004'535'809, 3), 2^21
//   (2'013'265'921, 31), 2^27
//   ntt(a, invert)   in-place NTT (inverse if invert); a.size() must be a power of 2 up to the max size, O(n log n)
//   multiply(a, b)   product of polynomials a and b mod MOD, O((n + m) log(n + m))
template <ll MOD, ll ROOT>
struct NTT {
    static void ntt(vector<ll> &a, bool invert = false) {
        int n = a.size();
        assert(n > 0 && (n & (n - 1)) == 0 && (MOD - 1) % n == 0);
        for (int i = 1, j = 0; i < n; i++) {  // bit-reversal permutation
            int bit = n >> 1;
            for (; j & bit; bit >>= 1) j ^= bit;
            j ^= bit;
            if (i < j) swap(a[i], a[j]);
        }
        for (int len = 2; len <= n; len <<= 1) {
            ll w = binexp(ROOT, (MOD - 1) / len, MOD);
            if (invert) w = binexp(w, MOD - 2, MOD);
            for (int i = 0; i < n; i += len) {
                ll wn = 1;
                for (int j = 0; j < len / 2; j++) {
                    ll u = a[i + j], v = a[i + j + len / 2] * wn % MOD;
                    a[i + j] = u + v < MOD ? u + v : u + v - MOD;
                    a[i + j + len / 2] = u - v >= 0 ? u - v : u - v + MOD;
                    wn = wn * w % MOD;
                }
            }
        }
        if (invert) {
            ll n_inv = binexp(n, MOD - 2, MOD);
            for (ll &x : a) x = x * n_inv % MOD;
        }
    }

    static vector<ll> multiply(vector<ll> a, vector<ll> b) {
        if (a.empty() || b.empty()) return {};
        int need = a.size() + b.size() - 1, n = 1;
        while (n < need) n <<= 1;
        for (ll &x : a) x = (x % MOD + MOD) % MOD;
        for (ll &x : b) x = (x % MOD + MOD) % MOD;
        a.resize(n);
        b.resize(n);
        ntt(a);
        ntt(b);
        for (int i = 0; i < n; i++) a[i] = a[i] * b[i] % MOD;
        ntt(a, true);
        a.resize(need);
        return a;
    }
};

// polynomial operations mod MOD, using NTT above; a[i] is the coefficient of x^i, all coefficients in [0, MOD)
// N = output length or combined input length
//   add(a, b)            a + b, O(n)
//   sub(a, b)            a - b, O(n)
//   mul(a, b)            a * b, O(n log n)
//   inv(a, n)            1 / a mod x^n; requires a[0] != 0, O(n log n)
//   sqrt(a, n)           square root of a mod x^n; requires a[0] == 1, O(n log n)
//   divmod(f, g)         {quotient, remainder} of f / g; the leading coefficient of g must be nonzero, O(N log N)
//   deriv(a)             derivative of a, O(n)
//   integ(a)             integral of a with constant term 0; requires deg a + 1 < MOD, O(n)
//   log(a, n)            natural log of a mod x^n; requires a[0] == 1, O(n log n)
//   exp(a, n)            exponential of a mod x^n; requires a[0] == 0, O(n log n)
//   pow(a, k, n)         a^k mod x^n for any k >= 0, O(n log n)
//   eval(f, x)           f(x), O(n)
//   multi_eval(f, xs)    f(x) for every x in xs, O(N log^2 N)
template <ll MOD, ll ROOT>
struct Poly {
    using V = vector<ll>;
    using N = NTT<MOD, ROOT>;

    static void trim(V &a) {
        while (!a.empty() && a.back() == 0) a.pop_back();
    }

    static V add(V a, const V &b) {
        a.resize(max(a.size(), b.size()));
        for (int i = 0; i < (int)b.size(); i++) a[i] = (a[i] + b[i]) % MOD;
        trim(a);
        return a;
    }

    static V sub(V a, const V &b) {
        a.resize(max(a.size(), b.size()));
        for (int i = 0; i < (int)b.size(); i++) a[i] = (a[i] - b[i] + MOD) % MOD;
        trim(a);
        return a;
    }

    static V mul(const V &a, const V &b) { return N::multiply(a, b); }

    static V inv(const V &a, int n) {
        V r{binexp(a[0], MOD - 2, MOD)};
        for (int m = 1; m < n; m *= 2) {
            V f(a.begin(), a.begin() + min((int)a.size(), 2 * m));
            f.resize(4 * m);
            r.resize(4 * m);
            N::ntt(f);
            N::ntt(r);
            for (int i = 0; i < 4 * m; i++) r[i] = r[i] * ((2 - f[i] * r[i] % MOD + MOD) % MOD) % MOD;
            N::ntt(r, true);
            r.resize(2 * m);
        }
        r.resize(n);
        return r;
    }

    static V sqrt(const V &a, int n) {
        assert(a[0] == 1);
        V r{1};
        ll half = (MOD + 1) / 2;
        for (int m = 1; m < n; m *= 2) {
            V f(a.begin(), a.begin() + min((int)a.size(), 2 * m));
            V q = mul(f, inv(r, 2 * m));  // r must be inverted to the new length, not the old one
            q.resize(2 * m);
            r.resize(2 * m);
            for (int i = 0; i < 2 * m; i++) r[i] = (r[i] + q[i]) % MOD * half % MOD;
        }
        r.resize(n);
        return r;
    }

    static pair<V, V> divmod(V f, V g) {
        trim(f);
        trim(g);
        assert(!g.empty());
        if (f.size() < g.size()) return {{}, f};
        int qn = f.size() - g.size() + 1;
        V rf(f.rbegin(), f.rend()), rg(g.rbegin(), g.rend());
        rf.resize(qn);
        V q = mul(rf, inv(rg, qn));
        q.resize(qn);
        reverse(q.begin(), q.end());
        V r = sub(f, mul(q, g));
        r.resize(min(r.size(), g.size() - 1));
        trim(r);
        return {q, r};
    }

    static V deriv(const V &a) {
        V r(max(0, (int)a.size() - 1));
        for (int i = 1; i < (int)a.size(); i++) r[i - 1] = a[i] * i % MOD;
        return r;
    }

    static V integ(const V &a) {
        int n = a.size();
        V r(n + 1), invs(max(2, n + 2), 1);
        for (int i = 2; i <= n; i++) invs[i] = (MOD - MOD / i) * invs[MOD % i] % MOD;
        for (int i = 0; i < n; i++) r[i + 1] = a[i] * invs[i + 1] % MOD;
        return r;
    }

    static V log(const V &a, int n) {
        assert(a[0] == 1);
        V d = deriv(V(a.begin(), a.begin() + min((int)a.size(), n)));
        V r = integ(mul(d, inv(a, n)));
        r.resize(n);
        return r;
    }

    static V exp(const V &a, int n) {
        assert(a.empty() || a[0] == 0);
        V r{1};
        for (int m = 1; m < n; m *= 2) {
            V l = log(r, 2 * m), g(2 * m, 0);
            for (int i = 0; i < min((int)a.size(), 2 * m); i++) g[i] = a[i];
            for (int i = 0; i < 2 * m; i++) g[i] = (g[i] - l[i] + MOD) % MOD;
            g[0] = (g[0] + 1) % MOD;
            r = mul(r, g);
            r.resize(2 * m);
        }
        r.resize(n);
        return r;
    }

    static V pow(const V &a, ll k, int n) {
        V res(n, 0);
        if (k == 0) {
            if (n) res[0] = 1;
            return res;
        }
        int t = 0;
        while (t < (int)a.size() && a[t] == 0) t++;
        if (t == (int)a.size() || (__int128)t * k >= n) return res;
        int m = n - t * k;  // a = c * x^t * b with b[0] == 1
        ll c = a[t], c_inv = binexp(c, MOD - 2, MOD);
        V b(m, 0);
        for (int i = 0; i < m && t + i < (int)a.size(); i++) b[i] = a[t + i] * c_inv % MOD;
        V l = log(b, m);
        for (ll &x : l) x = x * (k % MOD) % MOD;
        V e = exp(l, m);
        ll ck = binexp(c, k, MOD);
        for (int i = 0; i < m; i++) res[t * k + i] = e[i] * ck % MOD;
        return res;
    }

    static ll eval(const V &f, ll x) {
        ll res = 0;
        for (int i = (int)f.size() - 1; i >= 0; i--) res = (res * x + f[i]) % MOD;
        return res;
    }

    static V multi_eval(const V &f, const V &xs) {
        int n = xs.size();
        if (n == 0) return {};
        vector<V> tree(4 * n);
        function<void(int, int, int)> build = [&](int k, int l, int r) {
            if (r - l == 1) {
                tree[k] = {(MOD - xs[l] % MOD) % MOD, 1};
                return;
            }
            int m = (l + r) / 2;
            build(2 * k, l, m);
            build(2 * k + 1, m, r);
            tree[k] = mul(tree[2 * k], tree[2 * k + 1]);
        };
        build(1, 0, n);
        V ans(n);
        function<void(int, int, int, const V &)> go = [&](int k, int l, int r, const V &p) {
            if (r - l <= 32) {  // Horner is faster than dividing further on small ranges
                for (int i = l; i < r; i++) ans[i] = eval(p, xs[i]);
                return;
            }
            int m = (l + r) / 2;
            go(2 * k, l, m, divmod(p, tree[2 * k]).second);
            go(2 * k + 1, m, r, divmod(p, tree[2 * k + 1]).second);
        };
        go(1, 0, n, divmod(f, tree[1]).second);
        return ans;
    }
};

// long division of real polynomials: returns {quotient, remainder} of a / b; the leading coefficient of b must be nonzero, O(nm)
pair<vector<ld>, vector<ld>> poly_divide_real(vector<ld> a, const vector<ld> &b) {
    int n = a.size(), m = b.size();
    if (n < m) return {{}, a};
    vector<ld> q(n - m + 1);
    for (int i = n - m; i >= 0; i--) {
        q[i] = a[i + m - 1] / b[m - 1];
        for (int j = 0; j < m; j++) a[i + j] -= q[i] * b[j];
    }
    a.resize(m - 1);
    return {q, a};
}

// shortest linear recurrence of s mod a prime (Berlekamp-Massey), O(n^2)
// returns c so that s[i] = c[0] * s[i - 1] + c[1] * s[i - 2] + ... for every i >= c.size()
vector<ll> berlekamp_massey(const vector<ll> &s, ll mod) {
    int n = s.size(), len = 0, m = 0;
    vector<ll> cur(n + 1, 0), prev(n + 1, 0);
    cur[0] = prev[0] = 1;
    ll b = 1;
    for (int i = 0; i < n; i++) {
        m++;
        ll d = (s[i] % mod + mod) % mod;
        for (int j = 1; j <= len; j++) d = (d + cur[j] * ((s[i - j] % mod + mod) % mod)) % mod;
        if (d == 0) continue;
        vector<ll> saved = cur;
        ll coef = d * binexp(b, mod - 2, mod) % mod;
        for (int j = m; j < n + 1; j++) cur[j] = ((cur[j] - coef * prev[j - m]) % mod + mod) % mod;
        if (2 * len > i) continue;
        len = i + 1 - len;
        prev = saved;
        b = d;
        m = 0;
    }
    vector<ll> c(len);
    for (int i = 0; i < len; i++) c[i] = (mod - cur[i + 1]) % mod;
    return c;
}

// k-th term (0-indexed) of the recurrence s[i] = c[0] * s[i - 1] + c[1] * s[i - 2] + ..., mod a modulus below 2^31
// init holds the first c.size() terms, L = c.size(), O(L^2 log k)
ll kth_term(const vector<ll> &c, const vector<ll> &init, ll k, ll mod) {
    int len = c.size();
    if (len == 0) return 0;
    auto mul = [&](const vector<ll> &a, const vector<ll> &b) {  // a * b mod the characteristic polynomial
        vector<ll> res(2 * len - 1, 0);
        for (int i = 0; i < len; i++) {
            for (int j = 0; j < len; j++) res[i + j] = (res[i + j] + a[i] * b[j]) % mod;
        }
        for (int i = 2 * len - 2; i >= len; i--) {
            for (int j = 1; j <= len; j++) res[i - j] = (res[i - j] + res[i] * c[j - 1]) % mod;
        }
        res.resize(len);
        return res;
    };
    vector<ll> r(len, 0);
    r[0] = 1 % mod;
    for (int bit = 62; bit >= 0; bit--) {
        r = mul(r, r);
        if (k >> bit & 1) {  // multiply by x
            ll top = r[len - 1];
            for (int i = len - 1; i > 0; i--) r[i] = (r[i - 1] + top * c[len - 1 - i]) % mod;
            r[0] = top * c[len - 1] % mod;
        }
    }
    ll ans = 0;
    for (int i = 0; i < len; i++) ans = (ans + r[i] * ((init[i] % mod + mod) % mod)) % mod;
    return ans;
}

// value at x of the unique polynomial through (xs[i], ys[i]); xs distinct mod the prime mod, O(n^2 + n log mod)
ll lagrange(const vector<ll> &xs, const vector<ll> &ys, ll x, ll mod) {
    int n = xs.size();
    x = (x % mod + mod) % mod;
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ll num = (ys[i] % mod + mod) % mod, den = 1;
        for (int j = 0; j < n; j++) {
            if (j == i) continue;
            num = num * ((x - xs[j]) % mod + mod) % mod;
            den = den * ((xs[i] - xs[j]) % mod + mod) % mod;
        }
        ans = (ans + num * binexp(den, mod - 2, mod)) % mod;
    }
    return ans;
}

// value at x of the unique polynomial with p(i) = ys[i] for i = 0..n-1; requires the prime mod >= n, O(n + log mod)
ll lagrange_consecutive(const vector<ll> &ys, ll x, ll mod) {
    int n = ys.size();
    x = (x % mod + mod) % mod;
    if (x < n) return (ys[x] % mod + mod) % mod;
    vector<ll> pre(n + 1, 1), suf(n + 1, 1), inv_fac(n, 1);
    for (int i = 0; i < n; i++) pre[i + 1] = pre[i] * ((x - i + mod) % mod) % mod;
    for (int i = n - 1; i >= 0; i--) suf[i] = suf[i + 1] * ((x - i + mod) % mod) % mod;
    ll fac = 1;
    for (int i = 1; i < n; i++) fac = fac * i % mod;
    inv_fac[n - 1] = binexp(fac, mod - 2, mod);
    for (int i = n - 1; i > 0; i--) inv_fac[i - 1] = inv_fac[i] * i % mod;
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ll term = (ys[i] % mod + mod) % mod * pre[i] % mod * suf[i + 1] % mod * inv_fac[i] % mod * inv_fac[n - 1 - i] % mod;
        if ((n - 1 - i) & 1) term = (mod - term) % mod;
        ans = (ans + term) % mod;
    }
    return ans;
}
