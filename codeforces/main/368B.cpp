#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, m;
    cin >> n >> m;
    vector<ll> a(n), suff(n);
    for (ll i = 0; i < n; i++) cin >> a[i];

    set<ll> distinct;
    for (ll i = n - 1; i >= 0; i--) {
        distinct.insert(a[i]);
        suff[i] = distinct.size();
    }
    for (ll i = 0; i < m; i++) {
        ll l;
        cin >> l;
        cout << suff[l - 1] << "\n";
    }
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}