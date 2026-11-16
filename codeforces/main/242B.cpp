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
    vector<vector<ll>> segs(n);
    for (ll i = 0; i < n; i++) {
        ll li, ri;
        cin >> li >> ri;
        segs[i] = {li, ri, i + 1};
    }
    sort(segs.begin(), segs.end(), [](vector<ll> a, vector<ll> b) {
        return a[1] - a[0] < b[1] - b[0];
        });
    ll min_l = INF, max_r = -INF;
    for (ll i = 0; i < n; i++) {
        min_l = min(min_l, segs[i][0]);
        max_r = max(max_r, segs[i][1]);
    }
    if ((min_l == segs[n - 1][0]) && (max_r == segs[n - 1][1])) {
        cout << segs[n - 1][2];
    }
    else cout << "-1\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
