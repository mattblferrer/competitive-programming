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
    vector<ll> h(n);
    for (ll i = 0; i < n; i++) cin >> h[i];
    ll curr = 0;
    for (ll i = 0; i < k; i++) curr += h[i];
    ll minh = curr, ans = 0;
    for (ll i = k; i < n; i++) {
        curr += h[i] - h[i - k];
        if (curr < minh) {
            minh = curr;
            ans = i - k + 1;
        }
    }
    cout << ans + 1;
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}