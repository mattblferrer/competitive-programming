#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    string first, last;
    cin >> first >> last;
    string ans = "zzzzzz";
    for (ll i = 1; i <= first.size(); i++) {
        for (ll j = 1; j <= last.size(); j++) {
            string curr = first.substr(0, i) + last.substr(0, j);
            if (ans > curr) ans = curr;
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