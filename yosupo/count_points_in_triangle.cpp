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

// number of points of B strictly inside the triangle A[a] A[b] A[c], for many queries; |coordinates| up to 1e9
// in (x, y) order (as if rotated slightly, so no two x are equal), below[i][j] counts the B points strictly between
// A[i] < A[j] and strictly below the segment, on[i][j] those on it; a triangle is its upper chain minus its lower one
//   TriangleCounter(A, B)   precompute, O(|A|^2 |B|)
//   count(a, b, c)          points strictly inside A[a] A[b] A[c] (0 if degenerate), O(1)
struct TriangleCounter {
    vector<pll> A;
    vector<vector<int>> below, on;
    vector<int> same;  // number of B points equal to A[i]

    static ll cross(pll o, pll a, pll b) {
        return (a.first - o.first) * (b.second - o.second) - (a.second - o.second) * (b.first - o.first);
    }

    TriangleCounter(const vector<pll> &A, const vector<pll> &B): A(A), below(A.size(), vector<int>(A.size())), on(below), same(A.size()) {
        int n = A.size();
        for (int i = 0; i < n; i++) {
            for (const pll &q : B) same[i] += q == A[i];
            for (int j = 0; j < n; j++) {
                if (!(A[i] < A[j])) continue;
                for (const pll &q : B) {
                    if (!(A[i] < q && q < A[j])) continue;
                    ll c = cross(A[i], A[j], q);
                    if (c < 0) below[i][j]++;
                    else if (c == 0) on[i][j]++;
                }
            }
        }
    }

    int count(int a, int b, int c) const {
        if (A[b] < A[a]) swap(a, b);
        if (A[c] < A[b]) swap(b, c);
        if (A[b] < A[a]) swap(a, b);
        ll s = cross(A[a], A[c], A[b]);
        if (s == 0) return 0;
        if (s > 0) return below[a][b] + below[b][c] - below[a][c] - on[a][c];  // b above the segment a c
        return below[a][c] - below[a][b] - below[b][c] - on[a][b] - on[b][c] - same[b];
    }
};

void solve() {
    ll n, m, q;
    cin >> n;
    vector<pll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i].first >> a[i].second;
    cin >> m;
    vector<pll> b(m);
    for (ll i = 0; i < m; i++) cin >> b[i].first >> b[i].second;
    TriangleCounter tc(a, b);
    cin >> q;
    for (ll i = 0; i < q; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        cout << tc.count(x, y, z) << "\n";
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
