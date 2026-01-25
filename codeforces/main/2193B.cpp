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
    vector<ll> p(n);
    for (ll i = 0; i < n; i++) {
        cin >> p[i];
    }
    ll left = -1, right = -1;
    for (ll i = 0; i < n; i++) {
        if (p[i] != n - i) {
            left = i;
            break;
        }
    }
    if (left == -1) {
        for (ll i = 0; i < n; i++) cout << p[i] << " ";
        cout << "\n";
        return;
    }
    for (ll i = 0; i < n; i++) {
        if (p[i] == n - left) right = i;
    }
    reverse(p.begin() + left, p.begin() + right + 1);
    for (ll i = 0; i < n; i++) cout << p[i] << " ";
    cout << "\n";
    return;
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}