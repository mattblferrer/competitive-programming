// github.com/mattblferrer/competitive-programming

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
using ull = unsigned long long;
const ld PI = acosl(-1);
const ll INF = 2e18;
const ll MOD = 998'244'353;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

#ifdef LOCAL
#define dbg(x) cerr << #x << " = " << (x) << '\n'
#else
#define dbg(x)
#endif

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

using P = Poly<MOD, 3>;

void solve() {
    ll n, m;
    cin >> n >> m;
    vector<ll> c(n), p(m);
    for (ll i = 0; i < n; i++) cin >> c[i];
    for (ll i = 0; i < m; i++) cin >> p[i];
    vector<ll> b = P::multi_eval(c, p);
    for (ll i = 0; i < b.size(); i++) cout << b[i] << " ";
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
