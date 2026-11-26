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

// sum of r^i i^d over 0 <= i < n (0^0 = 1), mod a prime mod > d + 1, using lagrange_consecutive above; n = -1 gives the
// formal limit over all i >= 0, which needs r != 1. The sum f(n) is a polynomial of degree d + 1 if r == 1, and
// otherwise f(n) = c + r^n g(n) with deg g <= d; the (d + 1)-th difference of g(i) = (f(i) - c) r^-i vanishes, so
// c = (sum of (-1)^(d + 1 - i) C(d + 1, i) f(i) r^-i) / (r^-1 - 1)^(d + 1), and f(infinity) = c; i^d for i <= d + 1
// comes from a linear sieve, O(d + (d / log d) log mod)
ll sum_exp_poly(ll r, ll d, ll n, ll mod) {
    r %= mod;
    if (r == 0) return n != 0 && d == 0;
    int K = d + 2;
    vector<ll> f(K, 0);  // first i^d, then the prefix sums f(i)
    vector<int> lp(K), primes;
    f[0] = d == 0;
    f[1] = 1;
    for (int i = 2; i < K; i++) {
        if (!lp[i]) lp[i] = i, primes.push_back(i), f[i] = binexp(i, d, mod);
        for (int p : primes) {
            if (p > lp[i] || (ll)i * p >= K) break;
            lp[i * p] = p;
            f[i * p] = f[i] * f[p] % mod;
        }
    }
    vector<int>().swap(lp);
    ll run = 0;
    for (ll i = 0, pw = 1; i < K; i++, pw = pw * r % mod) {
        ll term = f[i] * pw % mod;
        f[i] = run;
        run = (run + term) % mod;
    }
    if (r == 1) {
        assert(n >= 0);
        return lagrange_consecutive(f, n, mod);
    }
    ll ri = binexp(r, mod - 2, mod), num = 0, binom = 1;  // binom = C(d + 1, i)
    vector<ll> inv(K, 1);
    for (int i = 2; i < K; i++) inv[i] = (mod - mod / i) * inv[mod % i] % mod;
    for (ll i = 0, pw = 1; i < K; i++, pw = pw * ri % mod) {
        ll t = binom * f[i] % mod * pw % mod;
        num = ((d + 1 - i) & 1 ? num - t + mod : num + t) % mod;
        if (i + 1 < K) binom = binom * ((d + 1 - i) % mod) % mod * inv[i + 1] % mod;
    }
    vector<ll>().swap(inv);
    ll c = num * binexp(binexp((ri - 1 + mod) % mod, d + 1, mod), mod - 2, mod) % mod;
    if (n < 0) return c;
    f.pop_back();  // g(0..d)
    for (ll i = 0, pw = 1; i <= d; i++, pw = pw * ri % mod) f[i] = (f[i] - c + mod) % mod * pw % mod;
    return (c + binexp(r, n, mod) * lagrange_consecutive(f, n, mod)) % mod;
}

void solve() {
    ll r, d;
    cin >> r >> d;
    cout << sum_exp_poly(r, d, -1, MOD) << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
