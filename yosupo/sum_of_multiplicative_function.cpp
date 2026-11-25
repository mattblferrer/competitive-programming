// github.com/mattblferrer/competitive-programming

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
using ull = unsigned long long;
const ld PI = acosl(-1);
const ll INF = 2e18;
const ll MOD = 469762049;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

#ifdef LOCAL
#define dbg(x) cerr << #x << " = " << (x) << '\n'
#else
#define dbg(x)
#endif

// sum of a multiplicative f over [1, n] mod mod (Min_25 sieve), n up to ~1e11; mod need not be prime, only below ~3e9
// so products fit in ll; f(p) on primes must be the polynomial coef[0] + coef[1] p + coef[2] p^2 + coef[3] p^3 (at
// most 4 terms), and fpe(p, e) gives f(p^e) mod mod
// first g[v] = sum of f(p) over primes p <= v for every v = n / i (Lucy's sieve, once per power of p), then
// S(v, j) = sum of f(i) over 2 <= i <= v whose smallest prime factor is >= primes[j], by recursion, O(n^(3/4) / log n)
template <class F>
ll multiplicative_sum(ll n, const vector<ll> &coef, F fpe, ll mod) {
    ll sq = sqrtl(n);
    while (sq * sq > n) sq--;
    while ((sq + 1) * (sq + 1) <= n) sq++;
    vector<ll> vals, primes;
    for (ll i = 1; i <= n; i = n / (n / i) + 1) vals.push_back(n / i);  // decreasing
    int m = vals.size();
    vector<int> lo(sq + 1), hi(sq + 1);  // index of v in vals: lo[v] if v <= sq, else hi[n / v]
    for (int i = 0; i < m; i++) (vals[i] <= sq ? lo[vals[i]] : hi[n / vals[i]]) = i;
    auto id = [&](ll v) { return v <= sq ? lo[v] : hi[n / v]; };
    vector<char> comp(sq + 1);
    for (ll p = 2; p <= sq; p++) {
        if (comp[p]) continue;
        primes.push_back(p);
        for (ll q = p * p; q <= sq; q += p) comp[q] = 1;
    }
    auto power_sum = [&](ll v, int k) -> ll {  // sum of i^k for i in [1, v] mod mod
        __int128 V = v;
        if (k == 0) return v % mod;
        if (k == 1) return (ll)(V * (V + 1) / 2 % mod);
        if (k == 2) return (ll)(V * (V + 1) * (2 * V + 1) / 6 % mod);
        ll t = (ll)(V * (V + 1) / 2 % mod);
        return t * t % mod;
    };
    vector<ll> G(m), g(m);
    for (int k = 0; k < (int)coef.size(); k++) {
        for (int i = 0; i < m; i++) g[i] = (power_sum(vals[i], k) + mod - 1) % mod;  // i = 2..v
        for (ll p : primes) {
            ll pk = 1, before = g[id(p - 1)];
            for (int t = 0; t < k; t++) pk = pk * (p % mod) % mod;
            for (int i = 0; i < m && vals[i] >= p * p; i++) {
                g[i] = (g[i] - pk * ((g[id(vals[i] / p)] - before + mod) % mod) % mod + mod) % mod;
            }
        }
        for (int i = 0; i < m; i++) G[i] = (G[i] + (coef[k] % mod + mod) % mod * g[i]) % mod;
    }
    auto S = [&](auto &self, ll v, int j) -> ll {
        if (j && primes[j - 1] >= v) return 0;
        ll res = (G[id(v)] - (j ? G[id(primes[j - 1])] : 0) + mod) % mod;  // the primes in [primes[j], v]
        for (int i = j; i < (int)primes.size() && primes[i] * primes[i] <= v; i++) {
            ll p = primes[i], pe = p;
            for (int e = 1; pe * p <= v; e++, pe *= p) {
                res = (res + fpe(p, e) % mod * self(self, v / pe, i + 1) + fpe(p, e + 1)) % mod;
            }
        }
        return res;
    };
    return (S(S, n, 0) + 1) % mod;
}

void solve() {
    ll n, a, b;
    cin >> n >> a >> b;
    auto f = [&](ll p, int e) { return (a * e + b * (p % MOD)) % MOD; };
    cout << multiplicative_sum(n, {a, b}, f, MOD) << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    cin >> t;  // comment out for single test
    while (t--) solve();
}
