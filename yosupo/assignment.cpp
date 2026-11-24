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

// minimum cost assignment (Hungarian) of every row to a distinct column; cost is n x m with n <= m, O(n^2 m)
// returns {total cost, match} where match[i] is the column assigned to row i
pair<ll, vector<int>> hungarian(const vector<vector<ll>> &cost) {
    int n = cost.size(), m = n ? cost[0].size() : 0;
    vector<ll> a(n + 1), b(m + 1);
    vector<int> p(m + 1), way(m + 1);  // p[j] = row matched to column j (1-indexed, 0 = none)
    for (int i = 1; i <= n; i++) {
        p[0] = i;
        int j0 = 0;
        vector<ll> minv(m + 1, INF);
        vector<char> used(m + 1, false);
        do {
            used[j0] = true;
            int i0 = p[j0], j1 = 0;
            ll delta = INF;
            for (int j = 1; j <= m; j++) {
                if (used[j]) continue;
                ll cur = cost[i0 - 1][j - 1] - a[i0] - b[j];
                if (cur < minv[j]) {
                    minv[j] = cur;
                    way[j] = j0;
                }
                if (minv[j] < delta) {
                    delta = minv[j];
                    j1 = j;
                }
            }
            for (int j = 0; j <= m; j++) {
                if (used[j]) {
                    a[p[j]] += delta;
                    b[j] -= delta;
                } else {
                    minv[j] -= delta;
                }
            }
            j0 = j1;
        } while (p[j0] != 0);
        for (; j0 != 0; j0 = way[j0]) p[j0] = p[way[j0]];
    }
    vector<int> match(n, -1);
    for (int j = 1; j <= m; j++) if (p[j]) match[p[j] - 1] = j - 1;
    return {-b[0], match};
}

void solve() {
    ll n;
    cin >> n;
    vector<vector<ll>> a(n, vector<ll>(n));
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < n; j++) cin >> a[i][j];
    }
    auto [cost, match] = hungarian(a);
    cout << cost << "\n";
    for (ll i = 0; i < n; i++) cout << match[i] << " ";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
