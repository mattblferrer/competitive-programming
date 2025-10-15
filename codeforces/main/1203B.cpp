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
    vector<ll> a(4*n);
    for (ll i = 0; i < 4*n; i++) cin >> a[i];
    sort(a.begin(), a.end());
    set<ll> areas;
    for (ll i = 0; i < 2*n; i += 2) {
        if ((a[i] != a[i + 1]) || (a[4*n - i - 1] != a[4*n - i - 2])) {
            cout << "NO\n";
            return;
        }
        ll area = a[i] * a[4*n - i - 1];
        areas.insert(area);
    }
    if (areas.size() == 1) cout << "YES\n";
    else cout << "NO\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}