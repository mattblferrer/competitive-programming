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

void solve() {
    ll n;
    cin >> n;
    vector<ll> c(n + 1);
    for (ll i = 1; i <= n; i++) cin >> c[i];

    vector<ll> left(n + 2, INF), right(n + 2, INF);
    for (ll i = 2; i <= n; i++) {
        if (c[i - 1] == c[i]) left[i] = left[i - 1] + 1;
        else left[i] = 1;
    }
    for (ll i = n; i >= 2; i--) {
        if (c[i - 1] == c[i]) right[i - 1] = right[i] + 1;
        else right[i - 1] = 1;
    }
    for (ll i = 1; i <= n; i++) cout << min(left[i], right[i]) << ' ';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
