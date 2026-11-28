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
    ll n, m;
    cin >> n >> m;
    vector<string> s(n);
    for (ll i = 0; i < n; i++) cin >> s[i];

    for (ll i = 0; i < n; i++) {
        ll cnt = 0;
        for (ll j = 0; j < m; j++) {
            if (s[i][j] == 'x') cnt++;
        }
        if (cnt == m) cout << "Faucet " << i + 1;
    }
    for (ll i = 0; i < m; i++) {
        ll cnt = 0;
        for (ll j = 0; j < n; j++) {
            if (s[j][i] == 'x') cnt++;
        }
        if (cnt == n) cout << "Drain " << i + 1;
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
