#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

void solve() {
    ll n;
    cin >> n;
    string s;
    cin >> s;
    vector<ll> ans(n, 1);
    set<ll> seen;
    seen.insert(1);
    for (ll i = 0; i < n - 1; i++) {
        ll move = 1;
        if (s[i] == '<') {
            while (seen.count(ans[i] - move)) move++;
            ans[i + 1] = ans[i] - move;
        }
        else {
            while (seen.count(ans[i] + move)) move++;
            ans[i + 1] = ans[i] + move;
        }
        seen.insert(ans[i + 1]);
    }
    ll adj = LLONG_MAX;
    for (ll i = 0; i < n; i++) {
        adj = min(adj, ans[i]);
    }
    for (ll i = 0; i < n; i++) {
        ans[i] += -adj + 1;
    }

    for (ll i = 0; i < n; i++) cout << ans[i] << " ";
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}