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
    for (ll x = max(0LL, n - 100LL); x < n; x++) {
        ll curr = x;
        string to_str = to_string(x);
        for (char c: to_str) {
            curr += c - '0';
        }
        if (curr == n) ans.push_back(x);
    }
    cout << ans.size() << "\n";
    for (ll i = 0; i < ans.size(); i++) cout << ans[i] << " ";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}