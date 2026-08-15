#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll a, b;
    cin >> a >> b;
    if (a + b == 9) cout << "Nine\n";
    else if (a - b == 9) cout << "Nine\n";
    else if (a * b == 9) cout << "Nine\n";
    else if (9 * b == a) cout << "Nine\n";
    else cout << "Nein\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}