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
    set<ll> g;
    for (ll i = 0; i < n; i++) {
        ll ai;
        cin >> ai;
        g.insert(ai);
    }
    ll ans = 0, curr = 0;
    while (curr <= x) { 
        ans++;
        if (g.count(ans) == 0) curr++;
    }
    ans--;
    cout << ans << "\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}