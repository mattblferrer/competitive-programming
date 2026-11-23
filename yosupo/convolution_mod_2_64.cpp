// github.com/mattblferrer/competitive-programming

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
using ull = unsigned long long;
const ld PI = acosl(-1);
const ll INF = 2e18;
const ll MOD = 1'000'000'007;
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

// Garner/CRT: combine residues r[j][i] mod primes ps[j] into the value mod `mod` (mod = 0 means mod 2^64);
// exact while each value is below the product of ps, O(len * k^2)
vector<ull> garner(const vector<vector<ll>> &r, const vector<ll> &ps, ull mod) {
    int k = ps.size(), len = r[0].size();
    vector<vector<ll>> pre(k, vector<ll>(k + 1, 1));  // pre[j][t] = ps[0] * ... * ps[t - 1] mod ps[j]
    vector<ll> inv(k), x(k);
    vector<ull> pm(k + 1, 1), res(len);  // pm[t] = ps[0] * ... * ps[t - 1] mod `mod`
    for (int j = 0; j < k; j++) {
        for (int t = 0; t < k; t++) pre[j][t + 1] = pre[j][t] * (ps[t] % ps[j]) % ps[j];
        inv[j] = binexp(pre[j][j], ps[j] - 2, ps[j]);
        pm[j + 1] = mod ? pm[j] * (ps[j] % mod) % mod : pm[j] * ps[j];
    }
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < k; j++) {  // value = x[0] + x[1] * ps[0] + x[2] * ps[0] * ps[1] + ...
            ll cur = r[j][i];
            for (int t = 0; t < j; t++) cur = (cur - x[t] * pre[j][t] % ps[j] + ps[j]) % ps[j];
            x[j] = cur * inv[j] % ps[j];
            res[i] = mod ? (res[i] + x[j] % mod * pm[j]) % mod : res[i] + x[j] * pm[j];
        }
    }
    return res;
}

// product of polynomials a and b mod 2^64, using five NTT primes and CRT, exact while (n + m) <= 2^21,
// O((n + m) log(n + m))
vector<ull> convolution_mod_2_64(const vector<ull> &a, const vector<ull> &b) {
    if (a.empty() || b.empty()) return {};
    auto red = [](const vector<ull> &v, ll p) {  // reduce as ull: values >= 2^63 don't fit in ll
        vector<ll> w;
        for (ull x : v) w.push_back(x % p);
        return w;
        };
    return garner({NTT<998'244'353, 3>::multiply(red(a, 998'244'353), red(b, 998'244'353)),
                   NTT<469'762'049, 3>::multiply(red(a, 469'762'049), red(b, 469'762'049)),
                   NTT<754'974'721, 11>::multiply(red(a, 754'974'721), red(b, 754'974'721)),
                   NTT<1'004'535'809, 3>::multiply(red(a, 1'004'535'809), red(b, 1'004'535'809)),
                   NTT<2'013'265'921, 31>::multiply(red(a, 2'013'265'921), red(b, 2'013'265'921))},
        {998'244'353, 469'762'049, 754'974'721, 1'004'535'809, 2'013'265'921}, 0);
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<ull> a(n), b(m);
    for (ll i = 0; i < n; i++) cin >> a[i];
    for (ll i = 0; i < m; i++) cin >> b[i];
    vector<ull> c = convolution_mod_2_64(a, b);
    for (int i = 0; i < c.size(); i++) cout << c[i] << " ";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
