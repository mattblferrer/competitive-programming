#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, m;
    cin >> n >> m;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end(), greater<ll>());
    ll left = 0, right = n + 1;
    while (right - left > 1) {
        ll mid = (left + right) / 2;
        ll f = 0;
        for (ll i = 0; i < n; i++) {
            f += max(0LL, a[i] - i / mid);
        }
        if (f >= m) right = mid; 
        else left = mid; 
    }
    ll f = 0;
    for (ll i = 0; i < n; i++) {
        f += max(0LL, a[i] - i / right);
    }
    if (f < m) cout << "-1\n";
    else cout << right << " ";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}