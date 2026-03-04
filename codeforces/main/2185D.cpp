#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, m, h;
    cin >> n >> m >> h;
    vector<ll> a(n), og(n);
    set<ll> change;
    for (ll i = 0; i < n; i++) {
        cin >> a[i];
        og[i] = a[i];
    }
    for (ll i = 0; i < m; i++) {
        ll bi, ci;
        cin >> bi >> ci;
        bi--;
        a[bi] += ci;
        change.insert(bi);
        if (a[bi] > h) {
            for (ll j: change) a[j] = og[j];
            change.clear();
        }
    }
    for (ll i = 0; i < n; i++) cout << a[i] << " ";
    cout << "\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}