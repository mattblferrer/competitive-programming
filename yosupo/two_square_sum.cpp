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
        if (b % 2) {
            ans = (ans * a) % mod;
        }
        a = (a * a) % mod;
        b >>= 1;
    }
    return ans;
}

// deterministic Miller-Rabin for any n fitting in ll, O(log n) multiplications
bool miller_rabin(ll n) {
    if (n < 2) return false;
    for (ll p : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n % p == 0) return n == p;
    }
    auto mul = [&](ll a, ll b) { return (ll)((__int128)a * b % n); };
    auto power = [&](ll a, ll e) {
        ll r = 1;
        for (; e; e >>= 1, a = mul(a, a)) if (e & 1) r = mul(r, a);
        return r;
    };
    ll d = n - 1;
    int s = __builtin_ctzll(d);
    d >>= s;
    for (ll base : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) {
        ll a = base % n;
        if (a == 0) continue;  // this base says nothing about n
        ll x = power(a, d);
        if (x == 1 || x == n - 1) continue;
        bool composite = true;
        for (int i = 1; i < s && composite; i++) {
            x = mul(x, x);
            if (x == n - 1) composite = false;
        }
        if (composite) return false;
    }
    return true;
}

// a nontrivial factor of a composite n (Pollard's rho, Brent's variant), O(n^(1/4) log n) expected; uses gcd in batches
ll pollard_rho(ll n) {
    if (n % 2 == 0) return 2;
    static mt19937_64 gen(chrono::steady_clock::now().time_since_epoch().count());
    auto mul = [&](ll a, ll b) { return (ll)((__int128)a * b % n); };
    while (true) {
        ll c = gen() % (n - 1) + 1, y = gen() % n, x = y, ys = y, q = 1, g = 1;
        auto f = [&](ll v) { return (ll)(((__int128)v * v + c) % n); };
        for (ll r = 1; g == 1; r *= 2) {
            x = y;
            for (ll i = 0; i < r; i++) y = f(y);
            for (ll k = 0; k < r && g == 1; k += 128) {
                ys = y;
                for (ll i = 0; i < min<ll>(128, r - k); i++) {
                    y = f(y);
                    q = mul(q, llabs(x - y));
                }
                g = gcd(q, n);
            }
        }
        if (g == n) {  // the batch overshot: step through it one at a time
            do {
                ys = f(ys);
                g = gcd(llabs(x - ys), n);
            } while (g == 1);
        }
        if (g != n) return g;
    }
}

// prime factors of n >= 1 in increasing order, with repeats; n can be any ll, O(n^(1/4) log n) expected
vector<ll> factorize(ll n) {
    vector<ll> res;
    for (ll p = 2; p < 100 && p * p <= n; p++) {
        while (n % p == 0) {
            res.push_back(p);
            n /= p;
        }
    }
    function<void(ll)> go = [&](ll x) {
        if (x == 1) return;
        if (miller_rabin(x)) {
            res.push_back(x);
            return;
        }
        ll d = pollard_rho(x);
        go(d);
        go(x / d);
    };
    go(n);
    sort(res.begin(), res.end());
    return res;
}

// a gcd of the Gaussian integers x = x.first + x.second i and y (unique up to the units 1, i, -1, -i); Euclid with the
// quotient rounded to the nearest Gaussian integer, so the remainder's norm at most halves; components up to ~1e18, O(log)
pll gaussian_gcd(pll x, pll y) {
    auto rdiv = [](__int128 a, __int128 b) {  // nearest integer to a / b for b > 0
        __int128 t = 2 * a + b, q = t / (2 * b);
        return t % (2 * b) && t < 0 ? q - 1 : q;
    };
    while (y.first || y.second) {
        __int128 n = (__int128)y.first * y.first + (__int128)y.second * y.second;
        __int128 re = rdiv((__int128)x.first * y.first + (__int128)x.second * y.second, n);  // x * conj(y) / n
        __int128 im = rdiv((__int128)x.second * y.first - (__int128)x.first * y.second, n);
        pll r((ll)(x.first - (re * y.first - im * y.second)), (ll)(x.second - (re * y.second + im * y.first)));
        x = y;
        y = r;
    }
    return x;
}

// all pairs (a, b) of integers >= 0 with a^2 + b^2 = n, sorted, n up to ~1e18; uses factorize and gaussian_gcd above
// a + bi runs over products of (1 + i)^e2, q^(e / 2) for each prime q = 3 mod 4 (none if e is odd) and, for each prime
// p = 1 mod 4, pi^t conj(pi)^(e - t) with pi = gcd(p, x + i), x^2 = -1 mod p; then over the 4 units, O(n^(1/4) + answers)
vector<pll> two_square_sum(ll n) {
    if (n == 0) return {{0, 0}};
    auto mul = [](pll x, pll y) {
        return pll((ll)((__int128)x.first * y.first - (__int128)x.second * y.second),
                   (ll)((__int128)x.first * y.second + (__int128)x.second * y.first));
    };
    vector<ll> f = factorize(n);
    vector<pll> cur{{1, 0}};
    for (size_t i = 0, j; i < f.size(); i = j) {
        ll p = f[i];
        for (j = i; j < f.size() && f[j] == p; j++) {}
        int e = j - i;
        if (p % 4 == 3 && e % 2) return {};
        if (p % 4 != 1) {
            pll z = p == 2 ? pll(1, 1) : pll(p, 0);
            for (int t = 0; t < (p == 2 ? e : e / 2); t++) for (pll &c : cur) c = mul(c, z);
            continue;
        }
        auto pw = [&](ll a, ll k) {
            ll r = 1;
            for (; k; k >>= 1, a = (ll)((__int128)a * a % p)) if (k & 1) r = (ll)((__int128)r * a % p);
            return r;
        };
        ll c = 2;
        while (pw(c, (p - 1) / 2) != p - 1) c++;  // c is a non-residue, so c^((p - 1) / 4) squares to -1
        pll g = gaussian_gcd({p, 0}, {pw(c, (p - 1) / 4), 1}), h(g.first, -g.second);
        vector<pll> pg(e + 1, {1, 0}), ph(e + 1, {1, 0}), nxt;
        for (int t = 1; t <= e; t++) pg[t] = mul(pg[t - 1], g), ph[t] = mul(ph[t - 1], h);
        for (pll z : cur) for (int t = 0; t <= e; t++) nxt.push_back(mul(z, mul(pg[t], ph[e - t])));
        cur = nxt;
    }
    vector<pll> res;
    for (pll z : cur) {
        for (int u = 0; u < 4; u++, z = pll(-z.second, z.first)) if (z.first >= 0 && z.second >= 0) res.push_back(z);
    }
    sort(res.begin(), res.end());
    res.erase(unique(res.begin(), res.end()), res.end());
    return res;
}

void solve() {
    ll q;
    cin >> q;
    while (q--) {
        ll n;
        cin >> n;
        vector<pll> res = two_square_sum(n);
        cout << res.size() << "\n";
        for (auto [a, b] : res) cout << a << " " << b << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
