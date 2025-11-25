#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, m;
    cin >> n >> m;
    ll n2 = 0, n3 = 0, m2 = 0, m3 = 0;
    while (n % 2 == 0) {
        n /= 2;
        n2++;
    }
    while (n % 3 == 0) {
        n /= 3;
        n3++;
    }
    while (m % 2 == 0) {
        m /= 2;
        m2++;
    }
    while (m % 3 == 0) {
        m /= 3;
        m3++;
    }
    if ((n != m) || (n2 > m2) || (n3 > m3)) {
        cout << -1;
        return;
    }
    cout << (m2 - n2) + (m3 - n3);
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}