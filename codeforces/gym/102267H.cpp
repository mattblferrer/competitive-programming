#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll v, s;
    cin >> v >> s;
    double total_angle = (v - 2) * 180;
    double angle = total_angle / v;
    double hyp = (1.0 / cos((angle / 2.0) * (M_PI / 180.0))) * s / 2.0;
    cout << M_PI * hyp * hyp;
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}