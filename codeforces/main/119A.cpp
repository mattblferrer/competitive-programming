#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll a, b, n;
    cin >> a >> b >> n;
    ll turn = 0;
    while (true) {
        if (turn) n -= gcd(b, n);
        else n -= gcd(a, n);
        turn = 1 - turn;
        if (n < 0) {
            cout << turn;
            return;
        }
    }
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}