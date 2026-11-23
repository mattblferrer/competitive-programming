// github.com/mattblferrer/competitive-programming

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
using ull = unsigned long long;
const ld PI = acosl(-1);
const ll INF = 2e18;
const ll MOD = 998244353;
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
//   mul(a, b)            a * b, O(n log n)
//   inv(a, n)            1 / a mod x^n; requires a[0] != 0, O(n log n)
//   deriv(a)             derivative of a, O(n)
//   integ(a)             integral of a with constant term 0; requires deg a + 1 < MOD, O(n)
//   log(a, n)            natural log of a mod x^n; requires a[0] == 1, O(n log n)
//   exp(a, n)            exponential of a mod x^n; requires a[0] == 0, O(n log n)
template <ll MOD, ll ROOT>
struct Poly {
    using V = vector<ll>;
    using N = NTT<MOD, ROOT>;

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
};

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

void solve() {
    int n;
    cin >> n;
    vector<ll> b = bell_ntt<MOD, 3>(n);
    for (int i = 0; i <= n; i++) cout << b[i] << " ";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
