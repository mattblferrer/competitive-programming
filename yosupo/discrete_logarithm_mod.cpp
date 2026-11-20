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

// smallest x >= 0 with a^x = b (mod m), -1 if none; baby-step giant-step, O(sqrt(m))
ll discrete_log(ll a, ll b, ll m) {
    a %= m, b %= m;
    ll k = 1LL, add = 0LL, g;
    while ((g = gcd(a, m)) > 1) {
        if (b == k) return add;
        if (b % g) return -1;
        b /= g, m /= g, ++add;
        k = (k * 1LL * a / g) % m;
    }

    ll n = sqrtl(m) + 1;
    ll an = 1LL;
    for (ll i = 0; i < n; ++i)
        an = (an * 1LL * a) % m;

    unordered_map<ll, ll> vals;
    for (ll q = 0, cur = b; q <= n; q++) {
        vals[cur] = q;
        cur = (cur * 1LL * a) % m;
    }

    for (ll p = 1, cur = k; p <= n; p++) {
        cur = (cur * 1LL * an) % m;
        if (vals.count(cur)) {
            ll ans = n * p - vals[cur] + add;
            return ans;
        }
    }
    return -1;
}

void solve() {
    ll a, b, m;
    cin >> a >> b >> m;
    cout << discrete_log(a, b, m) << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    cin >> t;  // comment out for single test
    while (t--) solve();
}
