#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    string s;
    cin >> s;
    string ans = "";
    char curr = '0';
    ll n = s.size();
    for (ll i = n - 1; i >= 0; i--) {
        if (s[i] >= curr) {
            curr = s[i];
            ans += s[i];
        }
    }
    reverse(ans.begin(), ans.end());
    cout << ans;
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}