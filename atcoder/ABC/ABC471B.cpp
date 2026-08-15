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
    vector<string> s(n);
    for (ll i = 0; i < n; i++) cin >> s[i];
    map<string, ll> cnt;
    for (ll i = 0; i < n; i++) {
        string curr = "";
        for (char c : s[i]) curr += tolower(c);
        cnt[curr]++;
    }
    ll ans = 0;
    for (auto &pair : cnt) {
        ans = max(ans, pair.second);
    }
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}