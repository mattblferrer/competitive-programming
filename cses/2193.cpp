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

// number of lattice points on the boundary of a polygon with integer vertices, O(n log C)
ll lattice_boundary(const vector<pll> &p) {
    ll ans = 0;
    for (int i = 0, n = p.size(), j = n - 1; i < n; j = i++)
        ans += gcd(llabs(p[i].first - p[j].first), llabs(p[i].second - p[j].second));
    return ans;
}

// number of lattice points strictly inside a polygon with integer vertices (Pick's theorem), O(n log C)
ll lattice_interior(const vector<pll> &p) {
    ll area2 = 0;
    for (int i = 0, n = p.size(), j = n - 1; i < n; j = i++)
        area2 += p[j].first * p[i].second - p[i].first * p[j].second;
    return (llabs(area2) - lattice_boundary(p) + 2) / 2;
}

void solve() {
    ll n;
    cin >> n;
    vector<pll> pts(n);
    for (auto &[xi, yi] : pts) cin >> xi >> yi;
    cout << lattice_interior(pts) << " " << lattice_boundary(pts) << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
