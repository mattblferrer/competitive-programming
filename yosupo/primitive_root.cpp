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

// smallest primitive root mod prime m, any m fitting in ll; uses factorize above
// O(m^(1/4) log m + g log^2 m) expected, where g is the answer (small in practice)
ll primitive_root(ll m) {
    if (m == 2) return 1;
    auto mul = [&](ll a, ll b) { return (ll)((__int128)a * b % m); };  // a * b overflows ll once m > ~3e9
    auto power = [&](ll a, ll e) {
        ll r = 1;
        for (; e; e >>= 1, a = mul(a, a)) if (e & 1) r = mul(r, a);
        return r;
        };
    ll phi = m - 1;
    vector<ll> fact = factorize(phi);  // Pollard's rho; trial division is ~1e9 steps when m - 1 = 2 * prime
    fact.erase(unique(fact.begin(), fact.end()), fact.end());
    for (ll x = 2; x < m; x++) {
        bool ok = true;
        for (ll p : fact) if (power(x, phi / p) == 1) {
            ok = false; break;
        }
        if (ok) return x;
    }
    return -1;
}

void solve() {
    ll p;
    cin >> p;
    cout << primitive_root(p) << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    cin >> t;  // comment out for single test
    while (t--) solve();
}
