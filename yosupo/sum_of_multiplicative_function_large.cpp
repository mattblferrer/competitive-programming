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

// sum of a multiplicative f over [1, n] mod mod (Min_25 sieve), n up to ~1e12 (1e13 takes ~30 s); mod need not be
// prime, only below ~3e9 so products fit in 64 bits; f(p) on primes must be the polynomial coef[0] + coef[1] p +
// coef[2] p^2 + coef[3] p^3 (at most 4 terms), and fpe(p, e) gives f(p^e) already reduced mod mod
// first g_d[v] = sum of p^d over primes p <= v for every v = n / i (Lucy's sieve, all d in one pass), then the sum over
// composites by recursion on the smallest prime factor, O(n^(3/4) / log n); v = n / i is stored at index i if i <= sq
// and at v otherwise, so lookups need no division (or one exact double division), and % mod is a Barrett reduction
template <class F>
ll multiplicative_sum(ll n, const vector<ll> &coef, F fpe, ll mod) {
    ll sq = sqrtl(n);
    while (sq * sq > n) sq--;
    while ((sq + 1) * (sq + 1) <= n) sq++;
    int nc = coef.size();
    ull M = mod, im = ~0ULL / M;
    auto red = [&](ull x) -> ull {  // x mod M for x < 2^63
        ull r = x - (ull)((unsigned __int128)x * im >> 64) * M;
        return r >= M ? r - M : r;
    };
    auto sub = [&](ull x, ull y) { return x >= y ? x - y : x + M - y; };
    auto power_sum = [&](ull v, int d) -> ull {  // sum of i^d for i in [1, v] mod M
        ull a = v, b = v + 1, c = 2 * v + 1;
        (a % 2 ? b : a) /= 2;  // a b = v (v + 1) / 2
        if (d == 0) return v % M;
        ull t = red(a % M * (b % M));
        if (d == 1) return t;
        if (d == 3) return red(t * t);
        (a % 3 == 0 ? a : b % 3 == 0 ? b : c) /= 3;  // a b c = v (v + 1) (2v + 1) / 6
        return red(red(a % M * (b % M)) * (c % M));
    };
    // gs[v * nc + d] for small v <= sq, gl[i * nc + d] for large v = n / i, i <= sq: sum of p^d over primes p in [2, v]
    vector<ull> gs((sq + 1) * nc), gl((sq + 1) * nc), pw(nc), sp(nc);
    for (ll v = 1; v <= sq; v++) {
        for (int d = 0; d < nc; d++) {
            gs[v * nc + d] = sub(power_sum(v, d), 1);
            gl[v * nc + d] = sub(power_sum(n / v, d), 1);
        }
    }
    vector<ll> primes;
    vector<char> comp(sq + 1);
    for (ll p = 2; p <= sq; p++) {
        if (comp[p]) continue;
        primes.push_back(p);
        for (ll q = p * p; q <= sq; q += p) comp[q] = 1;
        for (int d = 0; d < nc; d++) {
            pw[d] = d ? red(pw[d - 1] * (p % M)) : 1;
            sp[d] = gs[(p - 1) * nc + d];  // sum over primes < p
        }
        for (ll i = 1, lim = min(sq, n / (p * p)); i <= lim; i++) {
            ll ip = i * p;
            const ull *src = ip <= sq ? &gl[ip * nc] : &gs[(ll)((double)n / ip) * nc];
            for (int d = 0; d < nc; d++) gl[i * nc + d] = sub(gl[i * nc + d], red(pw[d] * sub(src[d], sp[d])));
        }
        for (ll v = sq; v >= p * p; v--) {
            const ull *src = &gs[v / p * nc];
            for (int d = 0; d < nc; d++) gs[v * nc + d] = sub(gs[v * nc + d], red(pw[d] * sub(src[d], sp[d])));
        }
    }
    vector<ull> cm(nc), Gs(sq + 1), Gl(sq + 1);  // G = sum of f(p) over primes p <= v
    for (int d = 0; d < nc; d++) cm[d] = (coef[d] % mod + mod) % mod;
    for (ll v = 1; v <= sq; v++) {
        for (int d = 0; d < nc; d++) {
            Gs[v] = red(Gs[v] + cm[d] * gs[v * nc + d]);
            Gl[v] = red(Gl[v] + cm[d] * gl[v * nc + d]);
        }
    }
    int P = primes.size();
    auto G = [&](ll v, ll x) { return x <= sq ? Gl[x] : Gs[v]; };  // G at v = n / x, no division
    // S(v, x, j) = sum of f(m) over 2 <= m <= v = n / x whose smallest prime factor is >= primes[j]; a child with no
    // composite left (next prime squared > w) is a difference of G, so it is not called
    auto S = [&](auto &self, ll v, ll x, int j) -> ull {
        ull res = sub(G(v, x), j ? Gs[primes[j - 1]] : 0);  // the primes in [primes[j], v]
        for (int i = j; i < P && primes[i] * primes[i] <= v; i++) {
            ll p = primes[i], w = v / p, xe = x * p;  // w = v / p^e, xe = x p^e
            for (int e = 1; w >= p; e++, w /= p, xe *= p) {
                bool leaf = i + 1 == P || primes[i + 1] * primes[i + 1] > w;
                ull rest = leaf ? sub(G(w, xe), Gs[p]) : self(self, w, xe, i + 1);
                res = red(res + red(fpe(p, e) * rest) + fpe(p, e + 1));
            }
        }
        return res;
    };
    return (S(S, n, 1, 0) + 1) % M;
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
