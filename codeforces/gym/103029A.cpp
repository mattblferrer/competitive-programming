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
    ll k;
    cin >> k;
    vector<ll> b(k);
    for (ll i = 0; i < k; i++) {
        cin >> b[i];
        b[i]--;
    }
    for (ll i = 0; i < k; i++) x -= a[b[i]];
    cout << x + 1 << "\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}