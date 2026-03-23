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
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];
    vector<ll> odds, evens;
    ll sum_odd = 0, sum_even = 0;
    for (ll i = 0; i < n; i++) { 
        if (a[i] % 2 == 0) {
            evens.push_back(a[i]);
            sum_even += a[i];
        }
        else {
            odds.push_back(a[i]);
            sum_odd += a[i];
        }
    }
    sort(odds.begin(), odds.end());
    sort(evens.begin(), evens.end());
    ll ans = sum_odd + sum_even;
    if (odds.size() == 0) {
        cout << "0\n";
        return;
    }
    for (ll i = 0; i*2 + 1 < odds.size(); i++) {
        ans -= odds[i];
    }
    cout << ans << "\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}