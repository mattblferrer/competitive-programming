#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

void solve() {
    ll n;
    cin >> n;
    vector<ll> b(n);
    for (ll i = 0; i < n; i++) cin >> b[i];

    set<ll> unique;
    for (ll i = 0; i < n; i++) {
        if (unique.count(b[i])) {
            cout << "YES\n";
            return;
        }
        unique.insert(b[i]);
    }
    cout << "NO\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}