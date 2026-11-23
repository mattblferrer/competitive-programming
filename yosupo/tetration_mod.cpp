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

// Euler's totient phi(n), O(sqrt n)
ll totient(ll n) {
    ll tot = n;
    for (ll i = 2; i * i <= n; i++) {
        if (n % i == 0) tot -= tot / i;
        while (n % i == 0) n /= i;
    }
    if (n > 1) tot -= tot / n;
    return tot;
}

// a^^b = a^(a^(...^a)) (b copies of a) mod m, with a^^0 = 1 and 0^0 = 1; a, b >= 0, m >= 1
// a^n = a^(n mod phi(m) + phi(m)) (mod m) once n >= log2(m), so recurse on phi(m) until it reaches 1
// O(sqrt(m) log m); uses totient above
ll tetration(ll a, ll b, ll m) {
    const ll CAP = 64;  // above log2(m) for every m in ll
    auto power = [](ll x, ll e, ll md) {
        ll r = 1 % md;
        for (x %= md; e; e >>= 1, x = (ll)((__int128)x * x % md)) if (e & 1) r = (ll)((__int128)r * x % md);
        return r;
    };
    auto exact = [&](ll k) {  // min(a^^k, CAP)
        if (a == 0) return (ll)(k % 2 == 0);
        if (a == 1) return 1LL;
        ll v = 1;
        for (ll i = 0; i < k && v < CAP; i++) {
            ll r = 1;
            for (ll j = 0; j < v && r < CAP; j++) r = min(CAP, r * min(a, CAP));
            v = r;
        }
        return v;
    };
    function<ll(ll, ll)> go = [&](ll b, ll m) -> ll {
        if (m == 1) return 0;
        if (b == 0) return 1;
        ll n = exact(b - 1);
        if (n < CAP) return power(a, n, m);
        ll ph = totient(m);
        return power(a, go(b - 1, ph) + ph, m);
    };
    return go(b, m);
}

void solve() {
    ll a, b, m;
    cin >> a >> b >> m;
    cout << tetration(a, b, m) << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    cin >> t;  // comment out for single test
    while (t--) solve();
}
