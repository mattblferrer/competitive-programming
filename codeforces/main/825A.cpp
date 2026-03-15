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
    string s;
    cin >> n >> s;
    string ans = "";
    ll curr = 0;
    for (ll i = 0; i < n; i++) {
        if (s[i] == '1') curr++;
        else {
            ans += curr + '0';
            curr = 0;
        }
    }
    ans += curr + '0';
    cout << ans << "\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}