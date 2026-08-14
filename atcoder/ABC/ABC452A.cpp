#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    int m, d;
    cin >> m >> d;
    if ((m == 1) && (d == 7)) cout << "Yes\n";
    else if ((m == 3) && (d == 3)) cout << "Yes\n";
    else if ((m == 5) && (d == 5)) cout << "Yes\n";
    else if ((m == 7) && (d == 7)) cout << "Yes\n";
    else if ((m == 9) && (d == 9)) cout << "Yes\n";
    else cout << "No\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}