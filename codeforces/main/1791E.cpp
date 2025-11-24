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
    ll pos = 0, neg = 0, sum = 0, small = INF;
    for (ll i = 0; i < n; i++) {
        if (a[i] > 0) pos++;
        else neg++;
        sum += abs(a[i]);
        small = min(small, abs(a[i]));
    }
    if (neg % 2 == 0) {
        cout << sum << "\n";
        return;
    }
    cout << sum - 2*small << "\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}