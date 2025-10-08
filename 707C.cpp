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
    if (n < 3) cout << "-1";
    else if (n == 4) cout << "3 5";
    else if (n % 2 == 1) cout << n * n / 2 << " " << n * n / 2 + 1;
    else if (n % 4 == 2) cout << (n * n / 8) * 2 << " " << (n * n / 8 + 1) * 2;
    else cout << n / 4 * 3 << " " << n / 4 * 5;
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}