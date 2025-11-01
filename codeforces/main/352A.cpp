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
    ll zeros = 0, fives = 0;
    for (ll i = 0; i < n; i++) {
        ll ai;
        cin >> ai;
        if (ai == 0) zeros++;
        else fives++;
    }
    if (zeros == 0) {
        cout << -1;
        return;
    }
    ll k = fives / 9;
    if (k == 0) {
        cout << 0;
        return;
    }
    for (ll i = 0; i < k * 9; i++) cout << '5';
    for (ll i = 0; i < zeros; i++) cout << '0';
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}