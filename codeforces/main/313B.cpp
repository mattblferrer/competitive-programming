#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    string s;
    cin >> s;
    ll n = s.size();
    vector<ll> pref(n + 1);
    for (ll i = 0; i < n; i++) {
        pref[i + 1] = pref[i] + (s[i] == s[i + 1]);
    }

    ll m;
    cin >> m;
    for (ll i = 0; i < m; i++) {
        ll l, r;
        cin >> l >> r;
        cout << pref[r - 1] - pref[l - 1] << "\n";
    }
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}