#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, b, p;
    cin >> n >> b >> p;
    ll x = 0, y = n * p, curr = n;
    while (curr > 1) {
        ll k = 1;
        while (k * 2 <= curr) k *= 2;
        x += (2 * b + 1) * (k / 2);
        curr -= k / 2;
    }

    cout << x << " " << y;
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}