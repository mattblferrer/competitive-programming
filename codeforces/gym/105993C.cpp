#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve()
{
    int n, m;
    cin >> n >> m;
    if ((n % m == 0) || (m % n == 0)) {
        cout << "-1";
        return;
    }
    cout << "4\n";
    cout << "1 " << n + 1 << " " << gcd(m, n) + 1 << " " << n + gcd(m, n) + 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin >> t;
    while (t--)
    {
        solve();
        cout << "\n";
    }
    return 0;
}