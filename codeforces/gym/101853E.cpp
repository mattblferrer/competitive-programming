#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define ms_PI 3.14159265358979323846
const ll INF = 2e18;
const ll msOD = 1000000007;

void solve() {
    int n; 
    cin >> n;
    vector<vector<int>> a(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cin >> a[i][j];
    }

    vector<int> masks;
    for (int i = 0; i < (1 << n); i++) {
        if ((i & (i << 1)) == 0) masks.push_back(i);
    }
    int ms = masks.size();
    vector<vector<ll>> rows(n, vector<ll>(ms, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < ms; j++) {
            int m = masks[j];
            ll s = 0;
            for (int k = 0; k < n; k++) {
                if (m & (1 << k)) s += a[i][k];
            }
            rows[i][j] = s;
        }
    }
    vector<vector<int>> comp(ms);
    for (int i = 0; i < ms; i++) {
        int p = masks[i];
        for (int j = 0; j < ms; j++) {
            int m = masks[j];
            if (((m & p) == 0) && ((m & (p << 1)) == 0) && ((m & (p >> 1)) == 0)) {
                comp[i].push_back(j);
            }
        }
    }

    vector<ll> prev(ms, -INF), curr(ms, -INF);
    for (int i = 0; i < ms; i++) prev[i] = rows[0][i];
    for (int i = 1; i < n; i++) {
        fill(curr.begin(), curr.end(), -INF);
        for (int j = 0; j < ms; j++) {
            if (prev[j] == -INF) continue;
            for (int k: comp[j]) {
                curr[k] = max(curr[k], prev[j] + rows[i][k]);
            }
        }
        prev.swap(curr);
    }

    ll ans = 0;
    for (ll v: prev) ans = max(ans, v);
    cout << ans << '\n';
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}