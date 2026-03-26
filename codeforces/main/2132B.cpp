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
    vector<ll> ans;
    for (ll i = 1; i < 19; i++) {
        ll k = powl(10, i) + 1;
        if (n % k == 0) ans.push_back(n / k);
    }
    if (ans.size() == 0) {
        cout << "0\n";
        return;
    }
    sort(ans.begin(), ans.end());
    cout << ans.size() << "\n";
    for (ll i = 0; i < ans.size(); i++) {
        cout << ans[i] << " ";
    }
    cout << "\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}