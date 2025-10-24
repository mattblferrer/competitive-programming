#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll limit = 1e16;
    ll ans = 0;
    for (ll i = 1; i * i <= limit; i++) {
        string nstr = to_string(i * i);
        for (ll j = 1; j < nstr.size(); j++) {
            string astr = nstr.substr(0, j);
            string bstr = nstr.substr(j, nstr.size() - j);
            if (bstr[0] == '0') continue;

            ll a = stoll(astr), b = stoll(bstr);
            string anew = to_string(a), bnew = to_string(b);
            if (a + b == i) {
                ans += i * i;
                break;
            }
        }
    }
    cout << ans;
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}