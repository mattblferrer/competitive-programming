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
            ll qm = Q[i ^ (n >> 1)];  // Q(-x) at w^i is Q at w^(i + n/2)
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

void solve() {
    ll d, k;
    cin >> d >> k;
    vector<ll> a(d), c(d);
    for (ll i = 0; i < d; i++) cin >> a[i];
    for (ll i = 0; i < d; i++) cin >> c[i];

    cout << kth_term_ntt<MOD, 3>(c, a, k);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
