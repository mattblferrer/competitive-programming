#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, a, b, c;
    cin >> n >> a >> b >> c;
    ll ans = 0;
    char curr = 'R';
    for (ll i = 0; i < n - 1; i++) {
        if (curr == 'R') {  // Rabbit
            if (a < b) {
                curr = 'O';
                ans += a;
            }
            else {
                curr = 'E';
                ans += b;
            }
        }
        else if (curr == 'E') {  // Eeyore
            if (b < c) {
                curr = 'R';
                ans += b;
            }
            else {
                curr = 'O';
                ans += c;
            }
        }
        else if (curr == 'O') {  // Owl
            if (a < c) {
                curr = 'R';
                ans += a;
            }
            else {
                curr = 'E';
                ans += c;
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