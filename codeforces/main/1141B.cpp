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
    vector<ll> a(2*n);
    for (ll i = 0; i < n; i++) { 
        cin >> a[i];
        a[i + n] = a[i];
    }
    ll curr = 0, ans = 0;
    for (ll i = 0; i < 2*n; i++) {
        if (a[i] == 1) curr++;
        else curr = 0;
        ans = max(ans, curr); 
    }
    cout << ans;
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}