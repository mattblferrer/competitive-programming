#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, x;
    cin >> n >> x;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end());

    ll left = -1, right = *max_element(a.begin(), a.end()) + x + 1;
    while (right - left > 1) {
        ll mid = (left + right) / 2;
        ll w = 0;
        for (ll i = 0; i < n; i++) {
            w += max(0LL, mid - a[i]);
        }
        if (w > x) right = mid; 
        else left = mid; 
    }
    cout << left << "\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}