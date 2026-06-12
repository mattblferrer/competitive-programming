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
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];

    sort(a.begin(), a.end());
    vector<vector<ll>> groups;
    vector<ll> curr = {1};
    for (ll i = 1; i < n; i++) {
        if (a[i] - a[i - 1] > k) {
            groups.push_back(curr);
            curr = {1};
        }
        else if (a[i] != a[i - 1]) {
            curr.push_back(1);
        }
        else curr.back()++;
    }
    groups.push_back(curr);

    for (ll i = 0; i < groups.size(); i++) {
        if (groups[i].size() > 1) {
            cout << "YES\n";
            return;
        }
        if (groups[i][0] % 2 == 0) {
            cout << "YES\n";
            return;
        }
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