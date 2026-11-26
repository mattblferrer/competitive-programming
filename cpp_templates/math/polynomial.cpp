// Contents
//   binexp                a^b mod mod, O(log b)
//   mod_sqrt              a square root of a mod the prime p, -1 if none (copy of the Number Theory one)
//   NTT                   number theoretic transform, each MOD and ROOT pair is its own type
//   Poly                  polynomial operations mod MOD, using NTT above; a[i] is the coefficient of x^i
//   poly_prod             product f[0] * f[1] * ... * f[k - 1] mod MOD, divide and conquer, O(N log N log k)
//   poly_divide_real      long division of real polynomials: returns {quotient, remainder} of a / b
//   berlekamp_massey      shortest linear recurrence of s mod a prime (Berlekamp-Massey), O(n^2)
//   kth_term              k-th term (0-indexed) of the recurrence s[i] = c[0] * s[i - 1] + c[1] * s[i - 2] + ...
//   kth_term_ntt          k-th term of a linear recurrence mod an NTT prime (Bostan-Mori), O(d log d log k)
//   bernoulli_ntt         Bernoulli numbers B[0..n] mod an NTT prime, with B[1] = -1/2, O(n log n)
//   bell_ntt              Bell numbers B[0..n] mod an NTT prime, as exp(e^x - 1), O(n log n)
//   taylor_shift          a(x + c) mod MOD (Taylor shift), O(n log n)
//   stirling1_ntt         signed Stirling numbers of the first kind s(n, k), k = 0..n, mod an NTT prime, O(n log n)
//   stirling2_ntt         Stirling numbers of the second kind S(n, k), k = 0..n, mod an NTT prime, O(n log n)
//   partition_ntt         partition numbers p(0..n) mod an NTT prime, O(n log n)
//   shift_samples         h(a), ..., h(a + m - 1) from h(0), ..., h(n - 1) (shift of sampling points), O((n + m) log(n + m))
//   FactorialMod          n! mod an NTT prime for any n < MOD, block table of (iV)!, O(V) per query
//   lagrange              value at x of the unique polynomial through (xs[i], ys[i])
//   lagrange_consecutive  value at x of the unique polynomial with p(i) = ys[i] for i = 0..n-1

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
using ull = unsigned long long;

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

// copy of mod_sqrt from number_theory.cpp, for Poly::sqrt; left out of the notebook (see Number Theory)
// a square root of a mod the prime p (Tonelli-Shanks), the smaller of the two; -1 if none exists; p below 2^31, O(log^2 p)
ll mod_sqrt(ll a, ll p) {
    a = (a % p + p) % p;
    if (a == 0 || p == 2) return a;
    if (binexp(a, (p - 1) / 2, p) != 1) return -1;
    ll r;
    if (p % 4 == 3) {
        r = binexp(a, (p + 1) / 4, p);
    } else {
        ll q = p - 1, z = 2;
        int s = 0;
        while (q % 2 == 0) {
            q /= 2;
            s++;
        }
        while (binexp(z, (p - 1) / 2, p) != p - 1) z++;
        int m = s;
        ll c = binexp(z, q, p), t = binexp(a, q, p);
        r = binexp(a, (q + 1) / 2, p);
        while (t != 1) {
            int i = 0;
            for (ll x = t; x != 1; x = x * x % p) i++;
            ll b = c;
            for (int j = 0; j < m - i - 1; j++) b = b * b % p;
            m = i;
            c = b * b % p;
            t = t * c % p;
            r = r * b % p;
        }
    }
    return min(r, p - r);
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
//   ntt(a, invert)   in-place NTT (inverse if invert) of a vector<ll> or vector<unsigned> (half the memory) with values in
//                    [0, MOD); a.size() must be a power of 2 up to the max size; the forward result is in bit-reversed
//                    order and the inverse expects that order (fine for pointwise products), O(n log n)
//   multiply(a, b)   product of polynomials a and b mod MOD, O((n + m) log(n + m))
//   multiply_large(a, b)   multiply for products longer than the max size, in blocks; pass a and b with move to save memory,
//                          O((n + m) log(max size) + n * m / max size)
template <ll MOD, ll ROOT>
struct NTT {
    template <class T>
    static void ntt(vector<T> &a, bool invert = false) {
        int n = a.size();
        assert(n > 0 && (n & (n - 1)) == 0 && (MOD - 1) % n == 0);
        static vector<T> rt(2, 1);  // rt[k + j] = w^j, w a primitive (2k)-th root of unity, for each power of 2 k
        for (static int k = 2; k < n; k *= 2) {
            rt.resize(n);
            ull z = binexp(ROOT, (MOD - 1) / (2 * k), MOD);
            for (int j = k; j < 2 * k; j++) rt[j] = j & 1 ? rt[j / 2] * z % MOD : rt[j / 2];
        }
        if (!invert) {  // decimation in frequency: no bit-reversal pass, output in bit-reversed order
            for (int k = n / 2; k >= 1; k /= 2) {
                for (int i = 0; i < n; i += 2 * k) {
                    for (int j = 0; j < k; j++) {
                        T &u = a[i + j], &v = a[i + j + k], x = u, y = v;
                        u = x + y < MOD ? x + y : x + y - MOD;
                        v = (ull)(x < y ? x + MOD - y : x - y) * rt[j + k] % MOD;
                    }
                }
            }
            return;
        }
        for (int k = 1; k < n; k *= 2) {  // decimation in time: bit-reversed input, natural order output
            for (int i = 0; i < n; i += 2 * k) {
                for (int j = 0; j < k; j++) {
                    T &u = a[i + j], &v = a[i + j + k], x = u, y = (ull)v * rt[j + k] % MOD;
                    u = x + y < MOD ? x + y : x + y - MOD;
                    v = x < y ? x + MOD - y : x - y;
                }
            }
        }
        reverse(a.begin() + 1, a.end());  // turns the transform with w into the one with w^-1
        ull n_inv = binexp(n, MOD - 2, MOD);
        for (T &x : a) x = x * n_inv % MOD;
    }

    static vector<ll> multiply(const vector<ll> &a, const vector<ll> &b) {
        if (a.empty() || b.empty()) return {};
        int need = a.size() + b.size() - 1, n = 1;
        while (n < need) n <<= 1;
        vector<unsigned> fa(n), fb(n);
        for (int i = 0; i < (int)a.size(); i++) fa[i] = (a[i] % MOD + MOD) % MOD;
        for (int i = 0; i < (int)b.size(); i++) fb[i] = (b[i] % MOD + MOD) % MOD;
        ntt(fa);
        ntt(fb);
        for (int i = 0; i < n; i++) fa[i] = (ull)fa[i] * fb[i] % MOD;
        ntt(fa, true);
        return vector<ll>(fa.begin(), fa.begin() + need);
    }

    static vector<ll> multiply_large(vector<ll> a, vector<ll> b) {
        if (a.empty() || b.empty()) return {};
        int need = a.size() + b.size() - 1, sz = (MOD - 1) & -(MOD - 1), L = sz / 2;  // sz = max size
        if (need <= sz) return multiply(a, b);
        auto blocks = [&](vector<ll> &v) {  // NTT of each length-L block of v, zero-padded to sz; frees v
            vector<vector<unsigned>> res;
            for (int i = 0; i < (int)v.size(); i += L) {
                vector<unsigned> blk(sz);
                for (int t = i; t < min((int)v.size(), i + L); t++) blk[t - i] = (v[t] % MOD + MOD) % MOD;
                ntt(blk);
                res.push_back(move(blk));
            }
            vector<ll>().swap(v);
            return res;
        };
        vector<vector<unsigned>> A = blocks(a), B = blocks(b);
        int na = A.size(), nb = B.size();
        vector<ll> res(need);
        vector<unsigned> c(sz);
        for (int k = 0; k < na + nb - 1; k++) {  // output block k = sum of A[i] * B[k - i], overlap-added at k * L
            fill(c.begin(), c.end(), 0);
            for (int i = max(0, k - nb + 1); i <= min(k, na - 1); i++) {
                for (int t = 0; t < sz; t++) c[t] = (c[t] + (ull)A[i][t] * B[k - i][t]) % MOD;
            }
            ntt(c, true);
            for (int t = 0; t < sz && (ll)k * L + t < need; t++) {
                ll &r = res[(ll)k * L + t];
                r = r + c[t] < MOD ? r + c[t] : r + c[t] - MOD;
            }
        }
        return res;
    }
};

// polynomial operations mod MOD, using NTT above; a[i] is the coefficient of x^i, all coefficients in [0, MOD)
// N = output length or combined input length
//   add(a, b)            a + b, O(n)
//   sub(a, b)            a - b, O(n)
//   mul(a, b)            a * b, O(n log n)
//   inv(a, n)            1 / a mod x^n; requires a[0] != 0, O(n log n)
//   sqrt(a, n)           a square root of a mod x^n, empty if none exists; uses mod_sqrt, O(n log n)
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
        int t = 0;  // a = x^t * b with b[0] != 0: needs t even and b[0] a square, then sqrt(a) = x^(t/2) * sqrt(b)
        while (t < (int)a.size() && a[t] == 0) t++;
        if (t >= n || t == (int)a.size()) return V(n, 0);
        ll s = mod_sqrt(a[t], MOD), half = (MOD + 1) / 2;
        if (t % 2 || s == -1) return {};
        V b(a.begin() + t, a.end()), r{s};  // Newton works from any r with r^2 = b[0], not just 1
        int m = n - t / 2;
        for (int k = 1; k < m; k *= 2) {
            V f(b.begin(), b.begin() + min((int)b.size(), 2 * k));
            V q = mul(f, inv(r, 2 * k));  // r must be inverted to the new length, not the old one
            q.resize(2 * k);
            r.resize(2 * k);
            for (int i = 0; i < 2 * k; i++) r[i] = (r[i] + q[i]) % MOD * half % MOD;
        }
        r.resize(m);
        r.insert(r.begin(), t / 2, 0);
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

// product f[0] * f[1] * ... * f[k - 1] mod MOD ({1} if f is empty), using NTT above; divide and conquer so each
// level multiplies polynomials of total length N = sum of f[i].size(), O(N log N log k)
template <ll MOD, ll ROOT>
vector<ll> poly_prod(const vector<vector<ll>> &f) {
    auto go = [&](auto &self, int l, int r) -> vector<ll> {
        if (r - l == 0) return {1};
        if (r - l == 1) return f[l];
        int m = (l + r) / 2;
        return NTT<MOD, ROOT>::multiply(self(self, l, m), self(self, m, r));
        };
    return go(go, 0, f.size());
}

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

// k-th term (0-indexed) of s[i] = c[0] * s[i - 1] + ... + c[d - 1] * s[i - d] mod an NTT prime, using NTT above
// (Bostan-Mori: k-th coefficient of P / Q, halving k each step); init holds the first d terms, O(d log d log k)
template <ll MOD, ll ROOT>
ll kth_term_ntt(const vector<ll> &c, const vector<ll> &init, ll k) {
    using N = NTT<MOD, ROOT>;
    int d = c.size();
    if (d == 0) return 0;
    vector<ll> q(d + 1);  // Q(x) = 1 - c[0] x - c[1] x^2 - ...
    q[0] = 1;
    for (int i = 0; i < d; i++) q[i + 1] = ((-c[i]) % MOD + MOD) % MOD;
    vector<ll> p = N::multiply(vector<ll>(init.begin(), init.begin() + d), q);
    p.resize(d);  // P(x) = init * Q mod x^d
    int n = 1;
    while (n < 2 * d + 1) n <<= 1;
    for (; k; k >>= 1) {
        vector<ll> P = p, Q = q, V(n);
        P.resize(n);
        Q.resize(n);
        N::ntt(P);
        N::ntt(Q);
        for (int i = 0; i < n; i++) {
            ll qm = Q[i ^ 1];  // Q(-x) at w^j is Q at w^(j + n/2), next to it in bit-reversed order
            P[i] = P[i] * qm % MOD;
            V[i] = Q[i] * qm % MOD;
        }
        N::ntt(P, true);
        N::ntt(V, true);
        for (int i = 0; i < d; i++) p[i] = P[2 * i + (k & 1)];
        for (int i = 0; i <= d; i++) q[i] = V[2 * i];
    }
    return p[0];
}

// Bernoulli numbers B[0..n] mod an NTT prime MOD > n + 1, with B[1] = -1/2, using Poly above
// x / (e^x - 1) = sum of B[i] x^i / i!, so invert (e^x - 1) / x = sum of x^i / (i + 1)!, O(n log n)
template <ll MOD, ll ROOT>
vector<ll> bernoulli_ntt(int n) {
    vector<ll> fac(n + 2, 1), ifac(n + 2, 1);
    for (int i = 1; i <= n + 1; i++) fac[i] = fac[i - 1] * i % MOD;
    ifac[n + 1] = binexp(fac[n + 1], MOD - 2, MOD);
    for (int i = n + 1; i > 0; i--) ifac[i - 1] = ifac[i] * i % MOD;
    vector<ll> a(n + 1);
    for (int i = 0; i <= n; i++) a[i] = ifac[i + 1];
    vector<ll> b = Poly<MOD, ROOT>::inv(a, n + 1);
    for (int i = 0; i <= n; i++) b[i] = b[i] * fac[i] % MOD;
    return b;
}

// Bell numbers B[0..n] mod an NTT prime MOD > n (number of partitions of a set of i elements), using Poly above
// sum of B[i] x^i / i! = exp(e^x - 1), O(n log n)
template <ll MOD, ll ROOT>
vector<ll> bell_ntt(int n) {
    vector<ll> fac(n + 1, 1), ifac(n + 1, 1);
    for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % MOD;
    ifac[n] = binexp(fac[n], MOD - 2, MOD);
    for (int i = n; i > 0; i--) ifac[i - 1] = ifac[i] * i % MOD;
    vector<ll> a = ifac;  // e^x - 1
    a[0] = 0;
    vector<ll> b = Poly<MOD, ROOT>::exp(a, n + 1);
    for (int i = 0; i <= n; i++) b[i] = b[i] * fac[i] % MOD;
    return b;
}

// a(x + c) mod MOD (Taylor shift), MOD a prime > deg a, using NTT above
// b[k] k! = sum over i >= k of a[i] i! c^(i - k) / (i - k)!, one convolution with the second factor reversed, O(n log n)
template <ll MOD, ll ROOT>
vector<ll> taylor_shift(vector<ll> a, ll c) {
    int n = a.size();
    if (!n) return a;
    vector<ll> fac(n, 1), ifac(n, 1), b(n);
    for (int i = 1; i < n; i++) fac[i] = fac[i - 1] * i % MOD;
    ifac[n - 1] = binexp(fac[n - 1], MOD - 2, MOD);
    for (int i = n - 1; i > 0; i--) ifac[i - 1] = ifac[i] * i % MOD;
    c = (c % MOD + MOD) % MOD;
    for (ll i = 0, pw = 1; i < n; i++, pw = pw * c % MOD) {
        a[i] = a[i] * fac[i] % MOD;
        b[n - 1 - i] = pw * ifac[i] % MOD;
    }
    vector<ll> prod = NTT<MOD, ROOT>::multiply(a, b);
    for (int k = 0; k < n; k++) a[k] = prod[n - 1 + k] * ifac[k] % MOD;
    return a;
}

// signed Stirling numbers of the first kind s(n, k), k = 0..n, mod an NTT prime MOD > n, using taylor_shift above:
// x(x - 1)...(x - n + 1) = sum of s(n, k) x^k, and (-1)^(n - k) s(n, k) counts permutations of n with k cycles
// doubling over the bits of n: f_2m(x) = f_m(x) f_m(x - m) and f_(m + 1)(x) = f_m(x) (x - m), O(n log n)
template <ll MOD, ll ROOT>
vector<ll> stirling1_ntt(int n) {
    vector<ll> f{1};
    int m = 0;
    for (int b = n ? __lg(n) : -1; b >= 0; b--) {
        if (m) f = NTT<MOD, ROOT>::multiply(f, taylor_shift<MOD, ROOT>(f, -m)), m *= 2;
        if (n >> b & 1) {
            f.push_back(0);
            for (int i = m + 1; i > 0; i--) f[i] = (f[i - 1] + (MOD - m) * f[i]) % MOD;
            f[0] = (MOD - m) * f[0] % MOD;
            m++;
        }
    }
    return f;
}

// Stirling numbers of the second kind S(n, k), k = 0..n, mod an NTT prime MOD > n (partitions of n elements into k
// non-empty sets), using NTT above: S(n, k) = sum over i of i^n / i! * (-1)^(k - i) / (k - i)!, O(n log n)
template <ll MOD, ll ROOT>
vector<ll> stirling2_ntt(int n) {
    vector<ll> fac(n + 1, 1), ifac(n + 1, 1), a(n + 1), b(n + 1);
    for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % MOD;
    ifac[n] = binexp(fac[n], MOD - 2, MOD);
    for (int i = n; i > 0; i--) ifac[i - 1] = ifac[i] * i % MOD;
    for (int i = 0; i <= n; i++) {
        a[i] = binexp(i, n, MOD) * ifac[i] % MOD;
        b[i] = i & 1 ? MOD - ifac[i] : ifac[i];
    }
    vector<ll> c = NTT<MOD, ROOT>::multiply(a, b);
    c.resize(n + 1);
    return c;
}

// partition numbers p(0..n) mod an NTT prime MOD, using Poly above: 1 / (sum of p(i) x^i) = product of (1 - x^k)
// = sum over all integers k of (-1)^k x^(k(3k - 1) / 2) (Euler's pentagonal theorem), so one inverse, O(n log n)
template <ll MOD, ll ROOT>
vector<ll> partition_ntt(int n) {
    vector<ll> a(n + 1);
    for (ll k = 0; k * (3 * k - 1) / 2 <= n; k++) {
        ll sign = k & 1 ? MOD - 1 : 1;
        a[k * (3 * k - 1) / 2] = sign;
        if (k && k * (3 * k + 1) / 2 <= n) a[k * (3 * k + 1) / 2] = sign;
    }
    return Poly<MOD, ROOT>::inv(a, n + 1);
}

// h(a), h(a + 1), ..., h(a + m - 1) mod MOD for the polynomial h of degree < n given by h[i] = h(i), i = 0..n-1
// (shift of sampling points: Lagrange interpolation as one convolution), using NTT above; MOD > n, and every
// a + k - i (0 <= k < m, 0 <= i < n) must be nonzero mod MOD, e.g. a >= n; O((n + m) log(n + m))
template <ll MOD, ll ROOT>
vector<ll> shift_samples(const vector<ll> &h, ll a, int m) {
    int n = h.size(), d = n - 1, L = n + m - 1;
    a = (a % MOD + MOD) % MOD;
    vector<ll> ifac(n, 1), f(n), x(L), pre(L + 1, 1), inv(L);
    for (int i = 1; i < n; i++) ifac[i] = ifac[i - 1] * i % MOD;
    ll t = binexp(ifac[d], MOD - 2, MOD);
    for (int i = d; i >= 0; i--) ifac[i] = t, t = t * max(i, 1) % MOD;  // now ifac[i] = 1 / i!
    for (int i = 0; i < n; i++) {  // h(i) / (i! (d - i)! (-1)^(d - i))
        f[i] = h[i] * ifac[i] % MOD * ifac[d - i] % MOD;
        if ((d - i) & 1) f[i] = (MOD - f[i]) % MOD;
    }
    for (int j = 0; j < L; j++) x[j] = ((a - d + j) % MOD + MOD) % MOD, pre[j + 1] = pre[j] * x[j] % MOD;
    t = binexp(pre[L], MOD - 2, MOD);
    for (int j = L - 1; j >= 0; j--) inv[j] = t * pre[j] % MOD, t = t * x[j] % MOD;  // inv[j] = 1 / x[j]
    vector<ll> c = NTT<MOD, ROOT>::multiply(f, inv), res(m);
    ll prod = pre[n];  // (a + k)(a + k - 1)...(a + k - d)
    for (int k = 0; k < m; k++) {
        res[k] = c[k + d] * prod % MOD;
        if (k + 1 < m) prod = prod * x[k + n] % MOD * inv[k] % MOD;
    }
    return res;
}

// n! mod MOD for any 0 <= n < MOD, MOD an NTT prime above 2^20, using shift_samples above
// g(x) = (Vx + 1)(Vx + 2)...(Vx + V) is sampled at 0..V directly, then shifted to 0..MOD/V, so block[i] = (iV)!
// construction O(V^2 + (MOD / V) log(MOD / V)), query O(V)
template <ll MOD, ll ROOT>
struct FactorialMod {
    static const int V = 1024;
    vector<ll> block;
    FactorialMod() {
        int K = (MOD - 1) / V + 1;
        vector<ll> g(V + 1, 1);
        for (int i = 0; i <= V; i++)
            for (int j = 1; j <= V; j++) g[i] = g[i] * ((ll)V * i + j) % MOD;
        vector<ll> rest = shift_samples<MOD, ROOT>(g, V + 1, K - V - 1);
        g.insert(g.end(), rest.begin(), rest.end());
        block.assign(K, 1);
        for (int i = 0; i + 1 < K; i++) block[i + 1] = block[i] * g[i] % MOD;
    }
    ll operator()(ll n) const {
        ll r = block[n / V];
        for (ll j = n / V * V + 1; j <= n; j++) r = r * j % MOD;
        return r;
    }
};

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
