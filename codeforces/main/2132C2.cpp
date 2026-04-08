#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    vector<ll> cost;
    ll c = 3, ctr = 1;
    for (ll i = 0; i < 30; i++) {
        cost.push_back(c);
        c = 3*c + ctr;
        ctr *= 3;
    }

    ll n, k;
    cin >> n >> k;
    ll min_n = n, min_k = 0;
    vector<ll> deals;
    while (min_n > 0) {
        min_k += min_n % 3;
        deals.push_back(min_n % 3);
        min_n /= 3;
    }
    if (k < min_k) {
        cout << "-1\n";
        return;
    }
    k = (k - min_k) / 2;
    for (ll i = deals.size() - 1; i >= 1; i--) {
        if (deals[i] <= k) {
            deals[i - 1] += 3*deals[i];
            k -= deals[i];
            deals[i] = 0;
        }
        else {
            deals[i - 1] += k*3;
            deals[i] -= k;
            break;
        }
    }
    ll ans = 0;
    for (ll i = deals.size() - 1; i >= 0; i--) ans += cost[i]*deals[i];
    cout << ans << "\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}