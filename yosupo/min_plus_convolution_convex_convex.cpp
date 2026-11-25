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

// c[k] = min over i + j = k of a[i] + b[j] for convex a and b (a[i + 1] - a[i] nondecreasing): c starts at
// a[0] + b[0] and its differences are those of a and b merged in sorted order, O(n + m)
vector<ll> min_plus_convex_convex(const vector<ll> &a, const vector<ll> &b) {
    int n = a.size(), m = b.size();
    vector<ll> c(n + m - 1);
    c[0] = a[0] + b[0];
    for (int i = 0, j = 0, k = 1; k < n + m - 1; k++) {
        if (j == m - 1 || (i < n - 1 && a[i + 1] - a[i] < b[j + 1] - b[j])) c[k] = c[k - 1] + a[i + 1] - a[i], i++;
        else c[k] = c[k - 1] + b[j + 1] - b[j], j++;
    }
    return c;
}

void solve() {
    ll n, m;
    cin >> n >> m;
    vector<ll> a(n), b(m);
    for (ll i = 0; i < n; i++) cin >> a[i];
    for (ll i = 0; i < m; i++) cin >> b[i];
    vector<ll> c = min_plus_convex_convex(a, b);
    for (ll i = 0; i < n + m - 1; i++) cout << c[i] << " ";
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
