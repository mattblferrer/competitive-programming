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
    ll curr = 0;
    for (ll i = 0; i < n; i++) {
        curr += a[i];
        if (curr > x) {
            cout << i;
            return;
        }
    }
    cout << n;
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}