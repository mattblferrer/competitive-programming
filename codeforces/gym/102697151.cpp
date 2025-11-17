#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    string s;
    cin >> s;
    double d;
    cin >> d;
    if (s == "sin") cout << sin(d);
    else if (s == "cos") cout << cos(d);
    else if (s == "tan") cout << tan(d);
    else if (s == "cosec") cout << 1/sin(d);
    else if (s == "sec") cout << 1/cos(d);
    else if (s == "cotan") cout << 1/tan(d);
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}