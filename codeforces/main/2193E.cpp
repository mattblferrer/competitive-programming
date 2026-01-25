#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n;
    cin >> n;
    set<ll> arr;
    for (ll i = 1; i <= n; i++) {
        ll ai;
        cin >> ai;
        arr.insert(ai);
    }
    vector<ll> ans(n + 1, INF);
    for (ll ai: arr) ans[ai] = 1;
    vector<vector<ll>> fac(n + 1);
    for (ll i: arr) {
        for (ll j = i; j <= n; j += i) {
            fac[j].push_back(i);
        }
    }
    for (ll i = 1; i <= n; i++) {
        for (ll f: fac[i]) ans[i] = min(ans[i], ans[i / f] + 1); 
    }
    for (ll i = 1; i <= n; i++) {
        if (ans[i] >= INF) cout << -1 << " ";
        else cout << ans[i] << " ";
    }
    cout << "\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}