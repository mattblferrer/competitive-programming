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
    vector<ll> s(n);
    for (ll i = 0; i < n; i++) cin >> s[i];

    vector<ll> ans;
    ll curr = 1;
    for (ll i = 1; i < n; i++) {
        if (s[i] == s[i - 1]) curr++;
        else {
            if (curr >= k) {
                for (ll j = 0; j < curr; j++) ans.push_back(s[i - 1]);
            }
            curr = 1;
        }
    }
    if (curr >= k) {
        for (ll i = 0; i < curr; i++) ans.push_back(s.back());
    }
    for (ll i = 0; i < ans.size(); i++) cout << ans[i] << " ";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}