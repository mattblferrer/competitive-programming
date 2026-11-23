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

// returns g = gcd(a, b) and sets x, y so that ax + by = g, O(log min(a, b))
ll extended_euclidean(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll gcd = extended_euclidean(b, a % b, y, x);
    y -= (a / b) * x;
    return gcd;
}

// inverse of a mod any modulus, -1 if gcd(a, mod) != 1, O(log mod)
ll modinv(ll a, ll mod) {
    ll x, y;
    ll gcd = extended_euclidean(a, mod, x, y);
    if (gcd != 1) return -1;  // doesn't exist
    return (x % mod + mod) % mod;
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

// some x with x^k = a (mod p) for a prime p, -1 if none (Adleman-Manders-Miller); k >= 0, 0^0 = 1
// reduces to g-th roots for g = gcd(k, p - 1), then takes one q-th root per prime factor q of g
// O(log^2 p + sqrt(q) log p) per prime q dividing g (with multiplicity); uses modinv and factorize above
ll kth_root_mod(ll a, ll k, ll p) {
    auto mul = [&](ll x, ll y) { return (ll)((__int128)x * y % p); };
    auto power = [&](ll x, ll e) {
        ll r = 1;
        for (; e; e >>= 1, x = mul(x, x)) if (e & 1) r = mul(r, x);
        return r;
    };
    a = (a % p + p) % p;
    if (k == 0) return a == 1 ? 1 : -1;
    if (a == 0) return 0;
    ll g = gcd(k, p - 1), m = (p - 1) / g;
    if (power(a, m) != 1) return -1;
    a = power(a, modinv(k / g % m, m));  // now any x with x^g = a works
    auto root = [&](ll a, ll r) {  // some x with x^r = a, for a prime r dividing p - 1 and an r-th power a
        ll s = 0, t = p - 1;
        while (t % r == 0) t /= r, s++;
        ll rho = 2;
        while (power(rho, (p - 1) / r) == 1) rho++;  // any non-r-th power
        ll z = power(rho, t), zinv = power(z, p - 2);  // z generates the subgroup of order r^s
        ll x = power(a, t == 1 ? 0 : modinv(r % t, t));  // x^r = a * (an element of that subgroup)
        ll h = mul(a, power(power(x, r), p - 2));  // the correction: find h = z^e, then x * z^(e / r) works
        ll top = 1;
        for (ll i = 0; i < s - 1; i++) top *= r;
        ll gam = power(z, top), M = sqrtl(r) + 1;  // gam has order r; baby-step giant-step for its logs
        vector<pll> baby(M);
        for (ll j = 0, cur = 1; j < M; j++, cur = mul(cur, gam)) baby[j] = {cur, j};
        sort(baby.begin(), baby.end());
        ll giant = power(power(gam, M), p - 2);
        auto dlog = [&](ll y) {  // d in [0, r) with gam^d = y
            for (ll i = 0; i <= M; i++, y = mul(y, giant)) {
                auto it = lower_bound(baby.begin(), baby.end(), pll(y, LLONG_MIN));
                if (it != baby.end() && it->first == y) return i * M + it->second;
            }
            return -1LL;
        };
        ll e = 0;
        for (ll i = 0, ri = 1, rest = top; i < s; i++, ri *= r, rest /= r)  // e one base-r digit at a time
            e += dlog(power(mul(h, power(zinv, e)), rest)) * ri;
        return mul(x, power(z, e / r));
    };
    for (ll q : factorize(g)) a = root(a, q);
    return a;
}

void solve() {
    ll k, y, p;
    cin >> k >> y >> p;
    cout << kth_root_mod(y, k, p) << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    cin >> t;  // comment out for single test
    while (t--) solve();
}
