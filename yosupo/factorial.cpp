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

FactorialMod<998'244'353, 3> fact;

void solve() {
    ll n;
    cin >> n;
    cout << fact(n) << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    cin >> t;  // comment out for single test
    while (t--) solve();
}
