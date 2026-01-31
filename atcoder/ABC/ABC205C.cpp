#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll a, b, c;
    cin >> a >> b >> c;
    if (c % 2 == 0) {
        if (abs(a) == abs(b)) cout << "=";
        else if (abs(a) < abs(b)) cout << "<";
        else cout << ">";
    }
    else if (a == b) cout << "=";
    else if (a < b) cout << "<";
    else cout << ">";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}