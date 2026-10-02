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
    string s;
    cin >> s;
    string ss = s;
    sort(ss.begin(), ss.end());
    ll cnt = 0;
    for (ll i = 0; i < n; i++) {
        if ((s[i] == '1') && (ss[i] == '0')) cnt++;
    }
    cout << cnt << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}