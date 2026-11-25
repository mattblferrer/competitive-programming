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

// derangements (Montmort numbers) mod any mod >= 1: d[k] = permutations of k elements with no fixed point, k = 0..n,
// from d[k] = (k - 1)(d[k - 1] + d[k - 2]); n * mod must fit in ll, O(n)
vector<ll> derangements(int n, ll mod) {
    vector<ll> d(n + 1, 0);
    d[0] = 1 % mod;
    for (ll k = 2; k <= n; k++) d[k] = (k - 1) * ((d[k - 1] + d[k - 2]) % mod) % mod;
    return d;
}

void solve() {
    ll n, m;
    cin >> n >> m;
    vector<ll> d = derangements(n, m);
    for (ll k = 1; k <= n; k++) cout << d[k] << " ";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
