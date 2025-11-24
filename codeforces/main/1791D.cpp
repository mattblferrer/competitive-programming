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
    string s;
    cin >> s;
    set<char> s1, s2;
    vector<ll> fa(n + 1), fb(n + 1);
    for (ll i = 0; i < n; i++) {
        s1.insert(s[i]);
        fa[i + 1] = s1.size();
    }
    for (ll i = n - 1; i >= 0; i--) {
        s2.insert(s[i]);
        fb[i] = s2.size();
    }
    ll ans = 0;
    for (ll i = 1; i < n; i++) {
        ans = max(ans, fa[i] + fb[i]);
    }
    cout << ans << "\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}