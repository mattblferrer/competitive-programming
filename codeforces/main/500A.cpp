#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, t;
    cin >> n >> t;
    t--;
    vector<ll> a(n - 1);
    for (ll i = 0; i < n - 1; i++) cin >> a[i];
    ll curr = 0;
    while (curr != n - 1) {
        curr = curr + a[curr];
        if (curr == t) {
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

    solve();
    return 0;
}