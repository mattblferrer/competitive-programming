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
    ll d = 0;
    for (ll i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            d += i;
            if (i != n / i) d += n / i;
        }
    }
    d -= n;  // don't count original n
    if (n == d) {
        cout << "PERFECT NUMBER\n" << d;
    }
    else {
        cout << "NOT A PERFECT NUMBER\n" << d;
    }
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}