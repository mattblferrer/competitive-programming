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

// c[k] = min over i + j = k of a[i] + b[j] for concave a (a[i + 1] - a[i] nonincreasing) and any b: on the cells
// (k, j) with 0 <= k - j < n the best j is nonincreasing in k, but the band of cells shifts right as k grows, so it
// is cut into full rectangles (halving the longer side) and each gets monotone minima, O((n + m) log^2 (n + m))
vector<ll> min_plus_concave_arbitrary(const vector<ll> &a, const vector<ll> &b) {
    int n = a.size(), m = b.size();
    vector<ll> c(n + m - 1, INF);
    auto mono = [&](auto &self, int klo, int khi, int jlo, int jhi) -> void {  // rows [klo, khi), best j in [jlo, jhi)
        if (klo >= khi) return;
        int k = (klo + khi) / 2, best = jlo;
        ll val = a[k - jlo] + b[jlo];
        for (int j = jlo + 1; j < jhi; j++) {
            if (a[k - j] + b[j] < val) val = a[k - j] + b[j], best = j;
        }
        c[k] = min(c[k], val);
        self(self, klo, k, best, jhi);
        self(self, k + 1, khi, jlo, best + 1);
    };
    auto rec = [&](auto &self, int klo, int khi, int jlo, int jhi) -> void {  // rows [klo, khi), columns [jlo, jhi)
        int lo = klo - (jhi - 1), hi = khi - 1 - jlo;  // range of k - j
        if (hi < 0 || lo >= n) return;
        if (lo >= 0 && hi < n) return mono(mono, klo, khi, jlo, jhi);
        if (khi - klo >= jhi - jlo) {
            int mid = (klo + khi) / 2;
            self(self, klo, mid, jlo, jhi);
            self(self, mid, khi, jlo, jhi);
        } else {
            int mid = (jlo + jhi) / 2;
            self(self, klo, khi, jlo, mid);
            self(self, klo, khi, mid, jhi);
        }
    };
    rec(rec, 0, n + m - 1, 0, m);
    return c;
}

void solve() {
    ll n, m;
    cin >> n >> m;
    vector<ll> a(n), b(m);
    for (ll i = 0; i < n; i++) cin >> a[i];
    for (ll i = 0; i < m; i++) cin >> b[i];
    vector<ll> c = min_plus_concave_arbitrary(a, b);
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
