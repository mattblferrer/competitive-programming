#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, k;
    cin >> n >> k;
    vector<ll> va(n), vb(n);
    map<ll, vector<ll>> a, b;
    for (ll i = 0; i < n; i++) {
        cin >> va[i];
        a[va[i]].push_back(i);
    }
    for (ll i = 0; i < n; i++) {
        cin >> vb[i];
        b[vb[i]].push_back(i);
    }
    ll la = 0, lb = 0;
    for (ll i = 0; i < n; i++) {
        if (k - va[i] <= 0) continue;
        la += distance(a[k - va[i]].begin(), 
            lower_bound(a[k - va[i]].begin(), a[k - va[i]].end(), i));
    }
    for (ll i = 0; i < n; i++) {
        if (k - vb[i] <= 0) continue;
        lb += distance(b[k - vb[i]].begin(), 
            lower_bound(b[k - vb[i]].begin(), b[k - vb[i]].end(), i));
    }
    if (la == lb) cout << "DRAW\n";
    else if (la > lb) cout << "MAHMOUD\n";
    else cout << "BASHAR\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}