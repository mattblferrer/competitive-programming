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

// c[k] = min over i + j = k of a[i] + b[j] for convex a and any b: the matrix b[j] + a[k - j] is Monge, so the
// best j is nondecreasing in k and divide and conquer over k (monotone minima) finds it, O((n + m) log(n + m))
vector<ll> min_plus_convex_arbitrary(const vector<ll> &a, const vector<ll> &b) {
    int n = a.size(), m = b.size();
    vector<ll> c(n + m - 1);
    auto rec = [&](auto &self, int klo, int khi, int jlo, int jhi) -> void {  // rows [klo, khi), best j in [jlo, jhi]
        if (klo >= khi) return;
        int k = (klo + khi) / 2, best = -1;
        for (int j = max(jlo, k - n + 1); j <= min({jhi, k, m - 1}); j++) {
            if (best == -1 || b[j] + a[k - j] < c[k]) c[k] = b[j] + a[k - j], best = j;
        }
        self(self, klo, k, jlo, best);
        self(self, k + 1, khi, best, jhi);
    };
    rec(rec, 0, n + m - 1, 0, m - 1);
    return c;
}

void solve() {
    ll n, m;
    cin >> n >> m;
    vector<ll> a(n), b(m);
    for (ll i = 0; i < n; i++) cin >> a[i];
    for (ll i = 0; i < m; i++) cin >> b[i];
    vector<ll> c = min_plus_convex_arbitrary(a, b);
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
